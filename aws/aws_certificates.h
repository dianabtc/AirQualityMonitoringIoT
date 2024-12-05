#ifndef AWS_CERTIFICATES_H
#define AWS_CERTIFICATES_H

#include <pgmspace.h>

#define THINGNAME "ESP32AirQuality"

const char AWS_IOT_ENDPOINT[] = "a2o3p0uz5lezih-ats.iot.eu-central-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAIarKx0YTlMYINom7cqjY9SmBt4AMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDEyMDUxNzE5
MzJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCfNysfCkn+P+Wj7s/F
nQFUYE2LD4asrpwnX6NGdkMH2jfq10ZbImoDhtisBIPy9h6R3qr/VrTgXhW7z69V
xGvH4r1imAnI/q2z7MQlY8msbMrirKJH5M/T9SJF/X1qVNxv3u6vZqGk1GtRa3MD
pEo1kR0dk1ZTUo8NdDgH71Cu9wAhNe6EGo93Zbp25OKK3cXFg4KypW8+m698MRg4
otNwX7ofa+d/YVrYAunEPovLSKKZfmk9PuRhkZRTexIgmlu9a3FpYHI1N9dL5FyX
HPP9Z7kWEoYYYcSxYOpeLek1JtIe3+yQ5HkCcCb5P5nbyZ/PECcH7tHYaqU+05J0
g5cNAgMBAAGjYDBeMB8GA1UdIwQYMBaAFDvPfVZr9pI6rThHCwNKm4cjyvaNMB0G
A1UdDgQWBBRASQMeel6K2+9PwCojjgoCnfNWoTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAO6GeGmeelH67x2HXHa3+neY4
VxOKMrSk8mXN4n0uDIpe7UfbPwjFJyWQ7fxQo9VlacLAAFlwgOIocQbYSe3DBFgO
nPUYfHCJatIhmgqXrex16skqaVDo9vQIDKJQTNV5l+RPc0AQVs/CGjrz2qtTn5I+
HwHBeD5thtvhSfSKJLqBEwtLnlNeXTOXA8LWULc9idlSOWMf1ssF6UutKvMqoYSR
x1PSQkRTZCexLIHkPyPcUNy8nqG8YZWvAO9t7K4JrpfSp1Ojo8u8XYmx+LtYB7sz
KDVanyecWFSk23qEYC6fIxevfkWZn79L+o65xGnoF0VqtFbhd7gcJDGs3qUshA==
-----END CERTIFICATE-----
)KEY";

// Device Private key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAnzcrHwpJ/j/lo+7PxZ0BVGBNiw+GrK6cJ1+jRnZDB9o36tdG
WyJqA4bYrASD8vYekd6q/1a04F4Vu8+vVcRrx+K9YpgJyP6ts+zEJWPJrGzK4qyi
R+TP0/UiRf19alTcb97ur2ahpNRrUWtzA6RKNZEdHZNWU1KPDXQ4B+9QrvcAITXu
hBqPd2W6duTiit3FxYOCsqVvPpuvfDEYOKLTcF+6H2vnf2Fa2ALpxD6Ly0iimX5p
PT7kYZGUU3sSIJpbvWtxaWByNTfXS+Rclxzz/We5FhKGGGHEsWDqXi3pNSbSHt/s
kOR5AnAm+T+Z28mfzxAnB+7R2GqlPtOSdIOXDQIDAQABAoIBADZQZqh3JRjUCW3s
KPr7/ZkgJTPcPxAnnOOdr6B49ZL3MX4upDSwv8OmO8Iq5Cx9I56VfHYQyTGFRxrD
1ceHc1FEG2FIBoaHwxAPJDaxHPpyPqAnTlECUJe5F1ETEba1bmHHhltVwqztPhMP
ebPzVtGBSJJvUdKo5l4rmHW0gSy+Umb3hien5axaZ5AkLsZkyhyk2+N99bo12oin
/yfrPCra2PdCH9CDEW0QR+x/MuBuvPtXcTwM3ol8MNL5TsmAWYn1+oRZv2AFmcC6
L9+KiH1S8vUiPU89Evqeckc/LciGV+iNRN52TENZ1+dARP3E14LE/qKYtCKFOTJb
OhFmMSECgYEA1AV3lVz+VpM0k1UWJqJbdqQWBm79ZxTl9TVOd+qPkZfamGrX+t2P
WV+QYj49JV5Ntl2MimpbnU6CLVdaztWkT33x9hq/jonGD8G4cIa9yS6SZNKX9Oi4
aWhRvXwct9DdcU6DF6PWeOEH1Q8xOTx+ZFrRbkoH+1Fun0CkXGFH4sUCgYEAwD2p
MpuwDnnFCabvQSnFTO1W5hkEKRe/rlzLqJWuuGpL/tZVQS/pXZaz/goKVrVUREbL
ie9o8dUdpKrHoHrG7ajze1ljkyP/A114JD5UYWT03Fo6kJ6f3JDNtrSXfwHJm6L4
eWqP8cxluq+NpcWNVUSguOgjkDfkMrNfhCklh6kCgYBByIh38WiAmB/h7q52wj06
rGKhEGLTTuqikC2Oi1qMQ99xFwV4MrI9eqcjtEfohj/6a0Al2iYewrMlOktUjXjz
qRIf1+DDav/m96YwU74i465MVgML3AELw3BJKG8IoWdztnZ6KT1sN/XkJ1iQd7KH
lJ4SaCnd0kBObRISD6TsOQKBgGXdhpWJh93zymPV8DuATcr4jK56nQjFS82x4Dzh
q+aOdNyBaEWVhLwRyiiX22icxx0ywlHB6cMTYZTK5eL0jAqNFw/KiwgB7/QxiCL0
YDQHkfRdX2EYnK78j/T7drdXFCSDU9TKkaHX5CPrOEyaBM0lA2FXqNiXtTTkdX2L
bBaZAoGBAKnBd0DPHjkYrs+aF1sCHLffzwTTD/wQUcHBei2KQrRVaHmOnePMQ13j
7EycHqm8YT1GTjIjPVWoRM705Dke+KW/V60KIGPAlpSvRzfpPH9k90UTMoLxyA5p
1wlJBtyDERhnKR/gTc0iVzAh35GKN7uGotFIpQev7KNyN55rKiHY
-----END RSA PRIVATE KEY-----
)KEY";

#endif