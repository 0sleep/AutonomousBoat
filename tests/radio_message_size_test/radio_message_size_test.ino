#include "radio_thread.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("HELLO");
  //Ensure message_t size is less than 32 bytes, RF24 only supports "classic" shockburst protocol
  Serial.println(sizeof(bad_message_t));
}

void loop() {
  delay(1000);
}

