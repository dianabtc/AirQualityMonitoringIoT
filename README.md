# Air Quality Monitoring IoT Project

## Description
The Air Quality Monitoring IoT project uses an ESP32 board to monitor air quality through temperature, humidity (DHT11) and gas (MQ135) sensors. The collected data is sent to AWS IoT Core and stored in DynamoDB, while a web interface displays this data in graphs. The project also includes fan control via commands sent through AWS IoT Core.

## File Structure: AirQualityMonitoringIoT
- AirQualityMonitoringIoT.ino
Main code for the ESP32:
  - Initializes WiFi connection, sensors, RGB LED, synchronization with the NTP server and connection to AWS IoT Core
  - Reads data from sensors and publishes it to AWS IoT Core
  - Updates the RGB LED to reflect air quality status
- sensors/
  - dht11.cpp/h
    Functions to initialize and read data from the DHT11 sensor
  - mq135.cpp/h
    Functions to initialize and read data from the MQ135 sensor
- aws/
  - aws_utils.cpp/h
    Functions for connecting to AWS IoT Core, publishing data to topics, subscribing and receiving from topics
  - aws_certificates.h
    Stores the certificate, private key and certificate authority for secure AWS IoT Core connection
- web_app/
  - server.js
    Backend server that fetches data from DynamoDB for graph visualization and publishes fan control commands to AWS IoT Core
  - index.html
    Frontend that displays sensors data using Chart.js and provides buttons to control the fan

## Setup and Installation
1. ESP32 Setup
   - Install ESP32 Driver: https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads
   - Install required libraries in Arduino IDE: WiFi, PubSubClient, ArduinoJson, DHT and MQ35 sensor library
   - Add ESP32 boards to Arduino IDE: go to File -> Preferences and add this URL https://dl.espressif.com/dl/package_esp32_index.json and then install esp32 from Board Manager
   - Configure AWS IoT Core Connections: create a Thing in AWS IoT Core, download the certificate, private key and CA and update aws_certificates.h
   - Configure WiFi with your credentials
2. AWS Setup
    - IoT Core: create the following MQTT topics: sensor/temperature, sensor/humidity, sensor/gas, commands/fan and set up rules to route data do DynamoDB
    - DynamoDB: create a table called SensorData with Partition Key: sensorType and Sort Key: timestamp, both strings
    - IAM Policy: create policies to allow ESP32 to iot:Connect, iot:Publish, iot:Subscribe, dynamodb:PutItem
3. Web Application Setup
    - Install Node.js and npm
    - Install dependencies: npm install aws-sdk express cors
    - Start the server: node server.js
    - View data in index.html
