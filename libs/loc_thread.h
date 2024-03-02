#ifndef LOC_THREAD_H
#define LOC_THREAD_H
#include "Wire.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

typedef enum {
  NO_FIX,
  2D_FIX,
  3D_FIX
} t_gnss_fix_type;

struct gnss_pos_t {
  double lat,
  double lon,
  double rot,
  t_gnss_fix_type fix_type
};


SFE_UBLOX_GNSS gnss;
rtos::Thread gnss_thread;
extern gnss_pos_t position;
bool gnss_thread_run = true;

//Start GNSS thread
extern int gnss_start(int update_rate);

//GNSS thread
void gnss_run();

//Stop GNSS thread
extern int gnss_stop();

#endif /* LOC_THREAD_H */
