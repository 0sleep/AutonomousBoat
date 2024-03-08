#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H
#include "mbed.h"
#include <SPI.h>
//#include "printf.h" //no printf for now, arduino-cli compiler errors :/
#include "RF24.h"
#include "pindef.h"
#include "loc_thread.h"
#include "sensor_thread.h"

#define SEND_QUEUE_LEN 20

typedef struct {
  int32_t lat; //decimal degrees //TODO: maybe store these as fixed-point
  int32_t lon; //decimal degrees
  uint8_t head; //heading in degrees
  uint8_t targetnum; //n-th waypoint that the boat is aiming at

  uint8_t turbidity;
  uint8_t conductivity;
  uint8_t fluorescence;
  uint8_t ph;
  uint8_t temperature;
  //message timestamp
  uint32_t unixEpoch;
} message_t;

class BoatRadio {
  public:
    //constructor
    BoatRadio();
    //set up all
    int begin();
    //This submits things into the radio to-send queue
    int send(gnss_pos_type *pos, sensor_data_t *sdata);
  private:
    rtos::Thread radioThread;
    void radioThread_run();
    // pipe addresses
    uint8_t address[2][6] = {"BOATP", "BASEP"};
    //memory pool
    rtos::MemoryPool<message_t, SEND_QUEUE_LEN> send_mpool;
    //message queue
    rtos::Queue<message_t, SEND_QUEUE_LEN> send_queue;
    //nRF radio object
    RF24 radio;
    //TODO: I might need to be able to keep track of the last radio.available() response
};

#endif /* RADIO_THREAD_H */
