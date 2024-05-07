#ifndef LOC_THREAD_H
#define LOC_THREAD_H
#include "Wire.h"
#include "mbed.h"
#include "mag_calibration.h"
#include <Adafruit_MMC56x3.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

typedef enum {
  FIX_NONE,
  FIX_2D,
  FIX_3D
} gnss_fix_type;

struct gnss_pos_type {
  int32_t lat;
  int32_t lon;
  float rot; // rot is in degrees!
  gnss_fix_type fix_type;
  uint32_t timestamp;
};


class Positioning {
  private:
    Adafruit_MMC5603 mmc;
    SFE_UBLOX_GNSS gnss;
    rtos::Thread gnss_thread;
    bool gnss_thread_run;
    //GNSS thread
    void gnss_run();

  public:
    gnss_pos_type position;
    //Start GNSS thread
    int gnss_start(int update_rate);
    //Stop GNSS thread
    int gnss_stop();
    //Get lat/lon as floats
    float get_lat();
    float get_lon();
}; 

#endif /* LOC_THREAD_H */
