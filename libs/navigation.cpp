#include "navigation.h"
#include "geo_utils.h"
Navigation::Navigation(Positioning* pos)
    : l_motor(LEFT_MOTOR_PIN), r_motor(RIGHT_MOTOR_PIN) {
  // store pointer to Positioning object
  pos_ptr = pos;
  kp = GAIN_KP;
  kd = GAIN_KD;
  ki = GAIN_KI;
}

void Navigation::begin() {
  // turn motors OFF
  l_motor.period(0.022);
  r_motor.period(0.022);
  l_motor.pulsewidth_us(1500);
  r_motor.pulsewidth_us(1500);
  // wait for GNSS fix
  // NOTE: this is currently blocking, which means other things running after
  // this call will be delayed until fix is received
  while (pos_ptr->position.fix_type == FIX_NONE) {
    thread_sleep_for(200);
  }
  // start controller thread
  controllerTicker.attach(mbed::callback(this, &Navigation::tickerCallback),
                          NAVIGATION_LOOP_SPEED);
}

void Navigation::tickerCallback() {
  // if close enough increase waypoint index + update current_waypoint
  if (distance_meters(pos_ptr->get_lat(), pos_ptr->get_lon(),
                      UINTCOORDS(current_waypoint.latitude),
                      UINTCOORDS(current_waypoint.longitude)) < 3) {
    // TODO advance next waypoint
  } else {
    // else:
    //   navigate!
    //   get heading error
    //   heading error is the difference between the current angle and the
    //   desired bearing the current angle is the bearing of the current
    //   position to the magnetic north pole + the current magnetometer
    //   reading
    float bearing_magnorth = bearing_degrees(
        pos_ptr->get_lat(), pos_ptr->get_lon(), MAG_NORTH_LAT, MAG_NORTH_LON);
    float bearing_target = bearing_degrees(
        pos_ptr->get_lat(), pos_ptr->get_lon(), UINTCOORDS(current_waypoint.latitude),
        UINTCOORDS(current_waypoint.longitude));
    // calculate current heading error (in degrees)
    error = bearing_target - (bearing_magnorth + pos_ptr->position.rot);
    //   update PID loop
    derivative_error = (float)(error - previous_error) / NAVIGATION_LOOP_SPEED;
    integral_error = integral_error + error * NAVIGATION_LOOP_SPEED;
    signal = kp * error + kd + derivative_error + ki * integral_error;
    //   send error into commandMotors() as turnspeed. movespeed = 0.5
    commandMotors(0.5, signal);
  }
}

// Set motor speeds according to some movement speed and some turning speed
/*
 *| Motor | Speed     |
 *|-------+-----------|
 *| Left  | move+turn |
 *| Right | move-turn |
 *|-------+-----------|
 */

void Navigation::commandMotors(float movespeed, float turnspeed) {
  const float l_speed = movespeed + turnspeed;
  const float r_speed = movespeed - turnspeed;
  const float l_clamped = max(1.0, min(-1.0, l_speed));
  const float r_clamped = max(1.0, min(-1.0, r_speed));
  l_motor.period_us(1100 + 100 * l_clamped);
  r_motor.period_us(1100 + 100 * r_clamped);
}

