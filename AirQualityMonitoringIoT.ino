#include <WiFi.h>
#include "MQ135.h"
#include "sensors/dht11.cpp"
#include "sensors/mq135.cpp"
#include "aws/aws_utils.cpp"

MQ135 gasSensor(MQ135_PIN);
float temperature = 0;
float humidity = 0;
float ppm = 0;

// RGB LED pins
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

// Configure Wi-Fi
const char* ssid = "DIGI-2HHy";
const char* password = "Za3PqdGs";

// Configure NTP
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7200;  // GMT+2
const int daylightOffset_sec = 3600;

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
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Synchronized with NTP.");
  initWiFi();
  initDHT11();
  initMQ135(gasSensor);
  connectAWS();
  Serial.println("Setup done!");
}

void loop() {
  client.loop();
  if (!client.connected()) {
    Serial.println("Client disconnected...");
  }

  updateLED(temperature, humidity, ppm);

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

void updateLED(float temperature, float humidity, float ppm) {
    if ((temperature >= 20 && temperature <= 25) &&
        (humidity >= 40 && humidity <= 60) &&
        (ppm < 800)) {
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
    } else if ((temperature >= 16 && temperature < 20) || (temperature > 25 && temperature <= 30) ||
               (humidity >= 30 && humidity < 40) || (humidity > 60 && humidity <= 70) ||
               (ppm >= 800 && ppm < 1500)) {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
    } else {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
    }
}