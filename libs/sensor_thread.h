#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "mbed.h"

typedef struct sensor_data_t {
  uint8_t turbidity;
  uint8_t conductivity;
  uint8_t fluorescence;
  uint8_t temperature;
};

class Sensor {
  public:
    Sensor();
    int begin();
    sensor_data_t sdata;
  private:
    rtos::Thread sensorThread;
    void sensorThread_run();
};

#endif /* SENSOR_DATA_H */
