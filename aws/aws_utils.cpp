#include "aws_utils.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

/* ESP32 will subscribe to topic commands/fan and turn on/off fan depending on message received. */
void callback(char* topic, byte* payload, unsigned int length) {
    String payloadStr = "";
    for (unsigned int i = 0; i < length; i++) {
        payloadStr += (char)payload[i];
    }

    // Parse JSON
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload, length);
    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    const char* command = doc["command"];
    if (!command) {
        Serial.println("No command found in JSON.");
        return;
    }

    // Execute command
    if (strcmp(command, "on") == 0) {
        digitalWrite(FAN_PIN, HIGH);
        Serial.println("Fan turned ON");
    } else if (strcmp(command, "off") == 0) {
        digitalWrite(FAN_PIN, LOW);
        Serial.println("Fan turned OFF");
    }
}

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

    pinMode(FAN_PIN, OUTPUT);
    client.setCallback(callback);
    if (client.subscribe("commands/fan")) {
        Serial.println("Subscribed to topic: commands/fan");
    } else {
        Serial.println("Failed to subscribe to topic.");
    }
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
    } else if (strcmp(sensor, "humidity") == 0) {
        client.publish(AWS_IOT_PUBLISH_HUMIDITY, jsonBuffer);
    } else if (strcmp(sensor, "gas") == 0) {
        client.publish(AWS_IOT_PUBLISH_GAS, jsonBuffer);
    }
}