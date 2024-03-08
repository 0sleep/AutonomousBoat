#include "radio_thread.h"

BoatRadio br;
Positioning loc;
Sensor sen;

void setup() {
  int err;
  Serial.begin(9600);
  while (!Serial);
  Serial.println("radio send test setup");
  err = br.begin();
  if (err) {
    Serial.print("Error in br.begin(): ");
    Serial.println(err);
  }
  err = loc.gnss_start(25);
  err = sen.begin();
}

void loop() {
  delay(100);
  br.send(&loc.position, &sen.sdata);
}
