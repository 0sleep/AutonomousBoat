#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "radio_thread.h" //for message structure

#define CE_PIN 10
#define CSN_PIN 9

/*
Reading pipe is "BOATP"
Writing pipe is "BASEP"

you should stay in reading mode forever
*/
void printStuff(message_t *messagebuffer) {
  Serial.println("------");
  Serial.print("LAT: ");
  Serial.println(messagebuffer->lat);
  Serial.print("LON: ");
  Serial.println(messagebuffer->lon);
  Serial.print("HEAD: ");
  Serial.println(messagebuffer->head);
  Serial.print("TURB: ");
  Serial.println(messagebuffer->turbidity);
  Serial.print("COND: ");
  Serial.println(messagebuffer->conductivity);
  Serial.print("FLUO: ");
  Serial.println(messagebuffer->fluorescence);
  Serial.print("TEMP: ");
  Serial.println(messagebuffer->temperature);
  Serial.print("EPOC: ");
  Serial.println(messagebuffer->unixEpoch);
  Serial.println();
}

RF24 radio(CE_PIN, CSN_PIN);
//char messagebuffer[32]; //32 is packet size for nrf24s
uint8_t address[][6] = {"BOATP", "BASEP"}; //receive pipe
message_t messagebuffer;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!radio.begin()) {Serial.println("Radio fail"); while (1);}
  radio.setPALevel(RF24_PA_HIGH); //RF_PA_MAX is deprecated
  radio.setPayloadSize(sizeof(message_t));
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.startListening();
}

void loop() {
  uint8_t pipe;
  //char messagebuffer[32];
  if (radio.available(&pipe)) {
    uint8_t bytes = radio.getPayloadSize(); // should be sizeof(message_t)
    radio.read(&messagebuffer, bytes); //read message into messagebuffer TODO read into struct
    Serial.println(bytes);
    printStuff(&messagebuffer);
  }
}

