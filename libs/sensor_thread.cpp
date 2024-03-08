#include "sensor_thread.h"

Sensor::Sensor() {
  //TODO all of the pindefs here
}

int Sensor::begin() {
  //start measurement thread
  sensorThread.start(mbed::callback(this, &Sensor::sensorThread_run));
  return 0;
}

void Sensor::sensorThread_run() {
  while (true) {
    //do some measurements
    sdata.temperature=rand();
    sdata.conductivity=rand();
    sdata.fluorescence=rand();
    sdata.turbidity=rand();
    thread_sleep_for(100);
  }
}
