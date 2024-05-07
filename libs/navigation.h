#ifndef _NAVIGATION_H
#define _NAVIGATION_H
#include "mbed.h"
#include "geo_utils.h"
#include "loc_thread.h"
#define NAVIGATION_LOOP_SPEED 0.2
#ifndef GAIN_KP
#define GAIN_KP 1
#endif
#ifndef GAIN_KD
#define GAIN_KD 0
#endif
#ifndef GAIN_KI
#define GAIN_KI 0
#endif

#include "pindef.h"

typedef struct {
  uint32_t latitude;
  uint32_t longitude;
} waypoint_t;

class Navigation {
 public:
  Navigation(Positioning* pos);
  // list of all waypoints
  waypoint_t waypoints[32];
  // currently selected waypoint
  waypoint_t current_waypoint;
  // current waypoint index
  uint8_t current_waypoint_index;
  // start navigation
  void begin();  //<-TODO: put PID gains in here?

 private:
  mbed::PwmOut l_motor;
  mbed::PwmOut r_motor;
  // pointer to positioning object
  Positioning* pos_ptr;
  // control thread
  mbed::Ticker controllerTicker;
  // control thread callback
  void tickerCallback();
  // controller values
  float kp, kd, ki;
  // errors
  float error, previous_error;
  // more
  float integral_error;
  float derivative_error;
  //"turn speed"
  float signal;
  // command motors
  void commandMotors(float movespeed, float turnspeed);
};
#endif /*_NAVIGATION_H*/
