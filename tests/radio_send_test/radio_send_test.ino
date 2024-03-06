#include "radio_thread.h"

BoatRadio br;

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
}

void loop() {
  delay(1000);
  br.send();
}
