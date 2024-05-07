#include "loc_thread.h"
//#define LOC_THREAD_DEBUG_ENABLED

int Positioning::gnss_start(int update_rate) {
  int err;
  gnss_thread_run = true;
  // Set up I2C
  Wire.begin();
  Wire.setClock(400000);
  // set up magnetometer
  mmc = Adafruit_MMC5603(12345);
  /* Initialise the sensor */
  if (!mmc.begin(MMC56X3_DEFAULT_ADDRESS, &Wire)) {  // I2C mode
    Serial.println("No mmc56x3 sensor found");
    return -1;
  }
  // Set GNSS default options
  if (gnss.begin() == false) {
    Serial.println("No GNSS detected.");
    return -1;
  }
  gnss.setI2COutput(COM_TYPE_UBX);
  gnss.setNavigationFrequency(update_rate);
#ifdef LOC_THREAD_DEBUG_ENABLED
  Serial.print("GNSS nav frequency set to");
  Serial.println(gnss.getNavigationFrequency());
#endif
  err = gnss_thread.start(mbed::callback(this, &Positioning::gnss_run));
  if (err) {
    // I really wish I was using zephyr here, I'm missing LOG_ERR already
    Serial.print("GNSS thread start failed: ");
    Serial.println(err);
    return -1;
  }

  return 0;
}

void Positioning::gnss_run() {
  byte fix_type;
  static float hi_cal[3];
  while (gnss_thread_run) {
    // From Example 7:
    //---------------
    // Query module every 25 ms. Doing it more often will just cause I2C
    // traffic. The module only responds when a new position is available. This
    // is defined by the update freq.
#ifdef LOC_THREAD_DEBUG_ENABLED
    Serial.println("GNSS loop");
#endif
    thread_sleep_for(25);
    // put position into struct
    position.lat = gnss.getLatitude();
    position.lon = gnss.getLongitude();
    position.timestamp = gnss.getUnixEpoch();
    // position.rot = gnss.getHead;
    fix_type = gnss.getFixType();
    switch (fix_type) {
      case 0:
        position.fix_type = FIX_NONE;
        break;
      case 2:
        position.fix_type = FIX_2D;
        break;
      case 3:
        position.fix_type = FIX_3D;
        break;
      default:  // Time only fix OR dead reckoning fixes, both of which are not
                // possible in this config
        position.fix_type = FIX_NONE;
    }
    // get most recent sensor event. TODO make magnetometer run in continuous
    // mode (getEvent is blocking-ish) and therefore probably slowing down data
    // acquisition
    sensors_event_t event;
    mmc.getEvent(&event);
    // Put raw magnetometer readings into an array
    float mag_data[] = {event.magnetic.x, event.magnetic.y, event.magnetic.z};
    // Apply hard-iron offsets
    hi_cal[0] = mag_data[0] - CAL_HARD_IRON_X;
    hi_cal[1] = mag_data[1] - CAL_HARD_IRON_Y;
    hi_cal[2] = mag_data[2] - CAL_HARD_IRON_Z;
    // Apply soft-iron scaling
    mag_data[0] = (CAL_SOFT_IRON_0_0 * hi_cal[0]) +
                  (CAL_SOFT_IRON_0_1 * hi_cal[1]) +
                  (CAL_SOFT_IRON_0_2 * hi_cal[2]);
    mag_data[1] = (CAL_SOFT_IRON_1_0 * hi_cal[0]) +
                  (CAL_SOFT_IRON_1_1 * hi_cal[1]) +
                  (CAL_SOFT_IRON_1_2 * hi_cal[2]);
    mag_data[2] = (CAL_SOFT_IRON_2_0 * hi_cal[0]) +
                  (CAL_SOFT_IRON_2_1 * hi_cal[1]) +
                  (CAL_SOFT_IRON_2_2 * hi_cal[2]);
    // Calculate current angle in xy plane
    position.rot = atan2(mag_data[1], mag_data[0]) * 180.0/M_PI;
  }
  // Thread has been stopped
  return;
}

int Positioning::gnss_stop() {
  gnss_thread_run = false;
  return 0;
}

float Positioning::get_lat() { return (position.lat / 10000000.0); }
float Positioning::get_lon() { return (position.lon / 10000000.0); }
