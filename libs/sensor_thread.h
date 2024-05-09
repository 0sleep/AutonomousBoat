#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "mbed.h"
#include "pindef.h"

typedef struct sensor_data_t {
  float turbidity;
  float conductivity;
  float fluorescence;
  float temperature;
};

class Sensor {
  public:
    Sensor();
    int begin();
    sensor_data_t sdata;
    //TEMP DEBUGGING FUNCTION
    void printData();
  private:
    rtos::Thread sensorThread;
    mbed::AnalogIn temp;
    mbed::AnalogIn cond;
    mbed::AnalogIn fluo;
    mbed::AnalogIn turb;
    void sensorThread_run();
};

#endif /* SENSOR_DATA_H */
