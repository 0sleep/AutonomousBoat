#ifndef LOC_THREAD_H
#define LOC_THREAD_H
#include "Wire.h"
#include "mbed.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

typedef enum {
  FIX_NONE,
  FIX_2D,
  FIX_3D
} gnss_fix_type;

struct gnss_pos_type {
  float lat;
  float lon;
  float rot;
  gnss_fix_type fix_type;
};


class Positioning {
  private:
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
}; 

#endif /* LOC_THREAD_H */
