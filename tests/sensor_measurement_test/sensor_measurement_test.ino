#include "sensor_thread.h"

Sensor sen;

void setup() {
  sen.begin();
}

void loop() {
  Serial.println(sen.sdata.temperature);
  delay(100);
}
