#include "navigation.h"
#include "loc_thread.h"
#include "mbed.h"

Positioning positioning;
Navigation navigation(&positioning);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  delay(100);
  Serial.println("Navigation Test");
  // set up GNSS
  positioning.gnss_start(25);
  // set up motor control
  navigation.current_waypoint = {
    530000000,
    -10000000
  };
  navigation.begin();
}

void loop() {}
