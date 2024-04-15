#include "mbed.h"

#define PUMP_PIN P0_30
/*
From experimentation:
+-------------+------------------+
|   Signal    |   Pump Status    |
+-------------+------------------+
| 300~1400us  | Clockwise        |
| 1400~1600us | Stop             |
| 1600~2600us | Counterclockwise |
+-------------+------------------+
Speed is dependent on distance to midpoint (1500us)

*/

mbed::PwmOut pump(PUMP_PIN);

void setup() {
  pump.period(0.02);
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("Pump test");
}

void loop() {
  for (int i=0; i<3000; i+=100) {
    pump.pulsewidth_us(i);
    Serial.println(i);
    thread_sleep_for(1000);
  }
}
