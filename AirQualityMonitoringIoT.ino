#include <WiFi.h>
#include "MQ135.h"
#include "sensors/dht11.cpp"
#include "sensors/mq135.cpp"
#include "aws/aws_utils.cpp"

MQ135 gasSensor(MQ135_PIN);
float temperature = 0;
float humidity = 0;
float ppm = 0;

// Configure Wi-Fi
const char* ssid = "DIGI-2HHy";
const char* password = "Za3PqdGs";

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 10000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println("Wi-Fi connected");
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  initDHT11();
  initMQ135(gasSensor);
  connectAWS();
  Serial.println("Setup done!");
}

void loop() {
  client.loop();

  if (millis() - lastPublishTime > publishInterval) {
    lastPublishTime = millis();
    
    temperature = readDHT11Temperature();
    humidity = readDHT11Humidity();
    ppm = readMQ135(gasSensor);

    publishSensorData("temperature", temperature);
    publishSensorData("humidity", humidity);
    publishSensorData("gas", ppm);

    Serial.print("Published data: temperature ");
    Serial.print(temperature);
    Serial.print("°C, humidity ");
    Serial.print(humidity);
    Serial.print("%, gas (ppm) ");
    Serial.println(ppm);
  }
}
