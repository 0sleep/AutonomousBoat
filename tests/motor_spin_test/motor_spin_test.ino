#include "mbed.h"
/* This program was intended to calibrate the motor controllers.
 * However, for the override board to function, the motor controllers must be
 * calibrated to the remote control instead. This means that the program must
 * emulate whatever the remote control outputs.
 */
#define MOTOR_PIN P0_4
#define PWMMAX 1880
#define PWMMIN 1100

mbed::PwmOut mot(MOTOR_PIN);

void setup() {
  mot.period(0.022);
  // MOTOR TRIM!!
  while (!Serial)
    ;
  //"turn on controller and put throttle in neutral position"
  /*
  mot.write(0.5);
  Serial.println("turn on esc now");
  delay(5000);
  Serial.println("push setup  button to set neutral pos");
  // clang-format off
  while (Serial.available() == 0) {Serial.println("Waiting for confirmation"); delay(100); }
  Serial.println("Push move to full throttle, then return to neutral");
  for (int i=50; i<PWMMAX; i++) {mot.write(i/100.0); delay(30);Serial.println(i);} //to full
  delay(1000);
  for (int i=PWMMAX; i>50; i--) {mot.write(i/100.0); delay(30);Serial.println(i);} //to neutral
  Serial.println("Push move to full reverse throttle, then return to neutral");
  delay(500);
  for (int i=50; i>PWMMIN; i--) {mot.write(i/100.0); delay(30);Serial.println(i);} //to zero
  delay(1000);
  for (int i=PWMMIN; i<50; i++) {mot.write(i/100.0); delay(30);Serial.println(i);} //to neutral
  Serial.println("Calibration complete!");
  // clang-format on
  delay(1000);
  */
}

void loop() {
//1.1ms to 1.88ms
  for (int i = PWMMIN; i < PWMMAX; i+=100) {
    Serial.println(i);
    mot.pulsewidth_us(i);
    delay(100);
  }
}
