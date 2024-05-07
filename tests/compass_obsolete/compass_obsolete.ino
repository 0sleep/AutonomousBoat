#include "LSM9DS1.h"

#define x_offset 1
#define y_offset 21

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  float x, y, z;

  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x, y, z);
    float h = (atan2(y,x) * 180) / PI;
    Serial.print(x);
    Serial.print(',');
    Serial.print(y);
    Serial.print(',');
    Serial.print(z);
    Serial.print(',');
    Serial.println(h);
  }
  delay(50);
}
