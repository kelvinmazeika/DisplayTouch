#include "secrets.h"
#include <Arduino.h>

const char* ssid = "SALA 09";
const char* password = "info@134";

//============================
// Debug
//============================
// 0 = sem mensagens
// 1 = apenas erros
// 2 = todas as mensagens
const int DEFAULT_DEBUG_LEVEL = 2;

// 4 = Pino utilizado para forçar todas as mensagens na inicialização
const int PINO_HABILITA_DEBUG_COMPLETO = 4;

//============================
// Mqtt
//============================


const char* MQTT_BROKER = "706524cf45374078abb8ff015db83f8c.s1.eu.hivemq.cloud";
const int MQTT_PORTA = 8883;

const char* MQTT_CLIENT_ID = "esp32_kelvin_mazeika";

const char* MQTT_USER = "kelvin";
const char* MQTT_PASSWORD = "Senai@134";

const bool MQTT_USE_TLS = false;

const char MQTT_CERTIFICADO_CA[] PROGMEM = R"EOF()EOF";

//============================
// TOPICOS
//============================
//! "senai134/shared/projeto/..." - formato do topico

const char* TOPICOS_PUBLICAR[] = 
{
    "senai/kelvin/esp32/status",
    "senai/kelvin/esp32/log",
    "senai/kelvin/esp32/resposta"
};

const int TOTAL_TOPICOS_PUBLICAR = sizeof(TOPICOS_PUBLICAR) / sizeof(TOPICOS_PUBLICAR[0]);

const char* TOPICOS_RECEBER[] =
{
    "senai/kelvin/esp32/comando",
    "senai/kelvin/esp32/config",
    "senai/kelvin/esp32/display"
};

const int TOTAL_TOPICOS_RECEBER = sizeof(TOPICOS_RECEBER) / sizeof(TOPICOS_RECEBER[0]);

//============================
// AWS
//============================

const bool USE_AWS_IOT = true;

const char* AWS_IOT_CLIENT_ID = "kelvinmzk";

const char AWS_CERT_CA[] PROGMEM = R"EOF(
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

const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUbKNPi7IDt/e43D4GknYf4Vb9P+YwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUxODE3MzIw
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKwbOVV501p55Dbn24if
QxeSBpKTzYDGPCwGx/mrRV7+80LjDCW3FzsTlJKvkH3hsADzoAfHMkt6BzjXg7oT
CxujTZB0JpfYozdq0ynIODKt85q0sxCmAqiLJ+ES+umsBkjlm4PRU6jiu9DRLtWN
esbziUzFmYA4fL3CncmMhKZ7+1sPkEqWHzINJAvFNAb4QWvZ7vUHIO8z8z4j5oQL
iOY5csuCuTgUaGhWHXEg28gqILZyAtLWpqCUL6WitaoUWCY8cLDIIsE0lTPOEFat
lC5wsAH8ejcJcclUxaX/uOBisPW6L3bXcRo5DvnATSLWYBEi2PGh3Ej5cJG6PvsY
S6sCAwEAAaNgMF4wHwYDVR0jBBgwFoAUYNFy/V/jGZvHnILsW9AcNWGDej0wHQYD
VR0OBBYEFHdEUHrkUCD3i4f/cqT1TM0iZ9P6MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAgMVubPo7Xry45OmrBFTOxuqlw
jj/eoN7ktrrZ7ZashgcL0LiQw6JHxICTD4zg5Py5awwsdBSllwD4VvRrwmrP3cSK
QKxyP+qYukNYTbCQN5HyEUsduPAS8nScai7ghx5PzzpVUyhQ/8lXAxoD6MKWdTko
9bmKjVeLyUBMlRg+CSoz8JXMIJ3a8SXJ7W+Y62ey9N5DdVHV9DSrX8emH3WI8k3/
nMJ/016sh0z1x3FAzOEgbVQ7fiFQikEj0X5KDDVplBTMINMYzizrHW3sFDKvccqX
3oyd8P7sIAiovjxVEYs9mqLQfxZ9F7uACuAO4bZlU3ApLYbQhedGgtNRl2la
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEArBs5VXnTWnnkNufbiJ9DF5IGkpPNgMY8LAbH+atFXv7zQuMM
JbcXOxOUkq+QfeGwAPOgB8cyS3oHONeDuhMLG6NNkHQml9ijN2rTKcg4Mq3zmrSz
EKYCqIsn4RL66awGSOWbg9FTqOK70NEu1Y16xvOJTMWZgDh8vcKdyYyEpnv7Ww+Q
SpYfMg0kC8U0BvhBa9nu9Qcg7zPzPiPmhAuI5jlyy4K5OBRoaFYdcSDbyCogtnIC
0tamoJQvpaK1qhRYJjxwsMgiwTSVM84QVq2ULnCwAfx6NwlxyVTFpf+44GKw9bov
dtdxGjkO+cBNItZgESLY8aHcSPlwkbo++xhLqwIDAQABAoIBABHm7wrOFkcGANAZ
RAOtFUyBWv+qMikf9ahauDhnMVsVR/aAKYZOyjLR8ZVkf7IoZKdksBO/C6NAOToX
aNNVIcWpMetBubX3ydp82SQyeG4FHB7OhwXHTuV7PBW0ZLcjtq+keo22m24oz4KE
D8wU4F2LfY+nyjTFK2yNrt4FKNMsTKbxhqxLnWnb3eGsIK9FuuCHDQ8FBNOiebGB
Hvze8rxHVkDEARxREvAzKP4P8nvzJIYrUaTW5jGcJefIf3zXMLXAh67elyQazYKZ
E8Djld1CR8sPigTJaOYkQEfo4JkxGfY51zy3+yexDiz5c1g6I/USzNYMU2ihhwwP
YBMsmqECgYEA1gbTgIKymnSKaG0Yasf69XvNaQKpDmGu4vOSxbc1zWXctoqNVuyn
zmolWuX5IZ0JYlWqgxVcqEadv9XTyNnY+GX6Gq64IwFONy3lfVnnEPDEwkKWwIw0
puyd/R5QP/uJl3y9giughCg48essL/chTtW85viaFbIED7TjSqY4v3sCgYEAzdvL
fdsa655Bg0USne6lyshboDGapsnIAjWoITapgnMabx2cgA/u3SpPzycw3qLvwavH
ZLInEyyfhPTu6QIAge0zhg+lf3EdjB+So6mLfQNO+43tZuNLjCCt+uH+sLugPPxR
YScK6wE9N65YBFKYG10EdecchoaM16iplcogVZECgYBVzPzDOyIgu3G1NW8hd7RK
72vEmlVtt4ll4GHJs431Hs3hvB+3Zj5LiNAa5bD/YbYeXttxm4G+0DhzbGRv062g
vzkJs1uMZPyXMGYc34q7htpKSmmnHU4KUTdw/tMLI2rgeRh788Nw17MkgLQBMqB+
uz70lVsoMWphZZHtHkAHuwKBgAa0zVlJRQQ+AJZdLrEUcDQ9+LYsR4R9eFWSF+sV
E8qbI1ZRWaLWYgq0cSsndLEcD8F4biN6pkk6n+u96vaOSSPybUZFxjdzoOnKsYVB
Zbjp3a3WPtCmQPTMr75HlHt/cUXrVl9a3UEwpiTlOhrR8gCaNCX/JG/BfF8eMIAf
uJPxAoGAe7qaMWjIspbBa4M7yutJLnXUMpiwta3tS0/vWmB53g4OGGPr7eCPwGAz
VbRm3DwPuu45QQue7fV5HKeno3FpDagyHIzT1sLFb1Hg6hrSht5sgTHk0/gaKhFs
UOks7vjdgTcQoZoIhBPB7r90tNaYyp8aCGn2dXGMGOJDRivc7uM=
-----END RSA PRIVATE KEY-----
)EOF";

const char* AWS_IOT_ENDPOINT = "a3mlj11myu5g6s-ats.iot.us-east-1.amazonaws.com";

const int AWS_IOT_PORT = 8883;

