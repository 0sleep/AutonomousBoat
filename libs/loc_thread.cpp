#include "loc_thread.h"
//#define LOC_THREAD_DEBUG_ENABLED

int Positioning::gnss_start(int update_rate) {
  int err;
  gnss_thread_run = true;
  //Set up I2C
  Wire.begin();
  Wire.setClock(400000);

  //Set GNSS default options
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
    //I really wish I was using zephyr here, I'm missing LOG_ERR already
    Serial.print("GNSS thread start failed: ");
    Serial.println(err);
    return -1;
  }

  return 0;
}


void Positioning::gnss_run() {
  byte fix_type;
  while (gnss_thread_run) {
  //From Example 7:
  //---------------
  //Query module every 25 ms. Doing it more often will just cause I2C traffic.
  //The module only responds when a new position is available. This is defined
  //by the update freq.
#ifdef LOC_THREAD_DEBUG_ENABLED 
    Serial.println("GNSS loop");
#endif
    thread_sleep_for(25);
    //put position into struct
    position.lat = gnss.getLatitude();
    position.lon = gnss.getLongitude();
    //FIXME
    //position.rot = gnss.getHead;
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
      default: //Time only fix OR dead reckoning fixes, both of which are not possible in this config
        position.fix_type = FIX_NONE;
    }
  }
  //Thread has been stopped
  return;
}

int Positioning::gnss_stop() {
  gnss_thread_run = false;
  return 0;
}
