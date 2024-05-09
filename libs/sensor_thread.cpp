#include "sensor_thread.h"

Sensor::Sensor(): temp(SENSE_TEMP_PIN), cond(SENSE_COND_PIN), fluo(SENSE_FLUO_PIN), turb(SENSE_TURB_PIN) {
}

int Sensor::begin() {
  //start measurement thread
  sensorThread.start(mbed::callback(this, &Sensor::sensorThread_run));
  return 0;
}

void Sensor::sensorThread_run() {
  while (true) {
    //do some measurements
    sdata.temperature=(temp.read());
    sdata.conductivity=(cond.read());
    sdata.fluorescence=(fluo.read());
    sdata.turbidity=(turb.read());
    thread_sleep_for(100);
  }
}

void Sensor::printData() {
  Serial.println("SENSOR DEBUG INFO");
  Serial.println("=================");
  Serial.print("TEMP: ");
  Serial.println(temp.read());
  Serial.print("COND: ");
  Serial.println(cond.read());
  Serial.print("FLUO: ");
  Serial.println(fluo.read());
  Serial.print("TURB: ");
  Serial.println(turb.read());
}

