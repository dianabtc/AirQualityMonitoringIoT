#include "mq135.h"

#define MQ135_PIN 32

void initMQ135(MQ135 gasSensor) {
    // set calibrated R0 maybe
}

/* Function to read ppm gas concentration */
float readMQ135(MQ135 gasSensor) {
  return gasSensor.getPPM();
}