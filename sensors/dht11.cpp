#include "dht11.h"
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void initDHT11() {
  dht.begin();
}

/* Functions to read temperature and air humidity */
float readDHT11Temperature() {
  return dht.readTemperature();
}

float readDHT11Humidity() {
  return dht.readHumidity();
}