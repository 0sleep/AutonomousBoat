#include "radio_thread.h"

//constructor
BoatRadio::BoatRadio(): radio(NRF_CE_PIN, NRF_CSN_PIN) {
  //Empty for now
}

int BoatRadio::begin() {
  if (!radio.begin()) {
    Serial.println("Radio hw not responding!");
    return -1;
  }
  radio.setPALevel(RF24_PA_HIGH);
  //set radio to transmit size of message_t
  radio.setPayloadSize(sizeof(message_t));
  //set up pipes
  radio.openWritingPipe(address[0]); //*boatp
  radio.openReadingPipe(1, address[1]); //*basep
  //put radion in RX mode
  radio.startListening();
  //start sending thread
  radioThread.start(mbed::callback(this, &BoatRadio::radioThread_run)); 
  return 0;
}

int BoatRadio::send() {
  //TODO gather current state of measurements etc. into a message_t struct
  //TODO submit struct to message queue
  //dummy data
  message_t *message = send_mpool.alloc();
  message->lat = 0.1;
  message->lon = 0.2;
  message->head = 53;
  message->turbidity = 21;
  message->conductivity = 3;
  message->fluorescence = 8;
  message->temperature = 21;
  message->unixEpoch=1709654255;
  send_queue.put(message);
  return 0;
}

void BoatRadio::radioThread_run() {
  bool err;
  while (true) {
    //try to get queued message
  //TODO: check if I can supply timeout for this, so I can try and radio.available() later
    osEvent evt = send_queue.get();     
    //ensure event is queue item
    if (evt.status == osEventMessage) {
      //get pointer
      message_t *message = (message_t *)evt.value.p;
      //write
      //reset err
      err = 0;
      while (err==0) {
        //Attempt to send message
        Serial.println("Attempting to send message");
        radio.stopListening(); //required
        err = radio.write(message, sizeof(message_t));
        Serial.println(err);
        radio.startListening();

        //random sleep amount to avoid sender and receiver synchronisation
        //thread_sleep_for(rand()%100);
        thread_sleep_for(100);
      }
      send_mpool.free(message);
      Serial.println("Message sent!");
      //message send success!
    }
  }
}
