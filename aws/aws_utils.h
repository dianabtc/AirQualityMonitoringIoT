#ifndef AWS_UTILS_H
#define AWS_UTILS_H

#include <Arduino_BuiltIn.h>
#include "aws_certificates.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>

#define AWS_IOT_PUBLISH_TEMPERATURE "sensor/temperature"
#define AWS_IOT_PUBLISH_HUMIDITY    "sensor/humidity"
#define AWS_IOT_PUBLISH_GAS         "sensor/gas"
#define FAN_PIN 14

void callback(char* topic, byte* payload, unsigned int length);
void connectAWS();
void publishMessage(const char* sensor, float value);

#endif