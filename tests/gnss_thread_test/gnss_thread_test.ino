#include "loc_thread.h"
Positioning p;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(200);
  Serial.println("Example: GNSS thread test");
  p.gnss_start(25);
}

void loop() {
  delay(10);
  if (p.position.fix_type != FIX_NONE) {
    Serial.print(p.position.lat);
    Serial.print(" ");
    Serial.print(p.position.lon);
    Serial.println();
  } else {
    Serial.println("No fix yet...");
  }
}
