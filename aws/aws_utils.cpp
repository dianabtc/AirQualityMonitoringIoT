#include "aws_utils.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void connectAWS() {
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  Serial.println("AWS IoT Connected!");
}

void publishSensorData(const char* sensor, float value) {
  StaticJsonDocument<200> doc;
  doc["sensorType"] = sensor;

  if (strcmp(sensor, "temperature") == 0) {
    doc["value"] = value;
  } else if (strcmp(sensor, "humidity") == 0) {
    doc["value"] = value;
  } else if (strcmp(sensor, "gas") == 0) {
    doc["value"] = value;
  }

  time_t now = time(nullptr);
  if (now < 100000) {
    Serial.println("Unsynchronized time, not publishing data.");
    return;
  }
  struct tm* timeInfo = localtime(&now);

  char timeBuffer[30];
  strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%dT%H:%M:%SZ", timeInfo);
  doc["timestamp"] = timeBuffer;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
 
  if (strcmp(sensor, "temperature") == 0) {
    client.publish(AWS_IOT_PUBLISH_TEMPERATURE, jsonBuffer);
    Serial.println("Published temperature data.");
  } else if (strcmp(sensor, "humidity") == 0) {
    client.publish(AWS_IOT_PUBLISH_HUMIDITY, jsonBuffer);
    Serial.println("Published humidity data.");
  } else if (strcmp(sensor, "gas") == 0) {
    client.publish(AWS_IOT_PUBLISH_GAS, jsonBuffer);
    Serial.println("Published gas data.");
  }
}