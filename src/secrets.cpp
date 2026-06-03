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
    "senai134/publisherTelaRetratil/esp32/comando",
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
MIIDWTCCAkGgAwIBAgIUU4HWM+XIvFPs/cRmT5eAHHiy92owDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUxODE3MzE1
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKVGKmBxpW3uo4mZJzGh
qxhVpn267df7teJWg8hKPAFQko2eQGMN4s1b6u9x9FSyh+zQChWmsY0o1dHMcfUJ
XKR5kR7aMfVDcivpImKaaMVTGcRemraMBcWleVYHDGN7lfW1O3TdkFMyPAjDPBd3
xvDdytZGtRbOk/4HsBUrA0aVNyg0xRy54oHem24B3WAz9jfyHjTmn/RXY8p6mNda
NfCc950X3v/cYaikkTGxZeQ4W8pt/PB4BOG6ZhW570uho1roP97SECgNQPBb3SJ8
Wy2Lp/5eD3siM3PwKl9VN280MXaUY+8XxzDM712ii7iE8YZrTW24FgPxLtDPouTO
io0CAwEAAaNgMF4wHwYDVR0jBBgwFoAUw9dMESJcmiZ5pHNhldKLMdVudIYwHQYD
VR0OBBYEFLNWJtBz9cFrWiEWWg8mAxqbCeSPMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBe6YdHhvZNCeYNeuYIEA9skt5+
iH4qQEXMPM8fE9LDnErX88cMU0yB0BAVQJcxZDQ1a6Y5ROSX1gE5BwF0AtC1NnGj
QwRs25cSf2Nx7+MBZvespKjsD+gk0aOe6KypZbcTq599GXHp6nyi3f3wL0FjLR29
kUTT2flq4EhW2LfkxJE6MYVY2EFcIORoydUP8OLbQtDWta3cBe+V447eCWz6HojD
DT1lijFjE0ALJWtybkURtEeD4jvhDo7RORV9BBkwmh56P/tHpPwU3Sg1V8576UzH
AIj+yGklTePEUWFpAi1nCbuN+3SnWbDatGEzc5lgqvAK8M8rZ1fYHQTgHcRk
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
	-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEApUYqYHGlbe6jiZknMaGrGFWmfbrt1/u14laDyEo8AVCSjZ5A
Yw3izVvq73H0VLKH7NAKFaaxjSjV0cxx9QlcpHmRHtox9UNyK+kiYppoxVMZxF6a
towFxaV5VgcMY3uV9bU7dN2QUzI8CMM8F3fG8N3K1ka1Fs6T/gewFSsDRpU3KDTF
HLnigd6bbgHdYDP2N/IeNOaf9FdjynqY11o18Jz3nRfe/9xhqKSRMbFl5Dhbym38
8HgE4bpmFbnvS6GjWug/3tIQKA1A8FvdInxbLYun/l4PeyIzc/AqX1U3bzQxdpRj
7xfHMMzvXaKLuITxhmtNbbgWA/Eu0M+i5M6KjQIDAQABAoIBAB/O2jcHiEQZCoZf
4Ggv6iLb0Rgfksjfm8i8x84TY2sJW7s/urqVoJHPX+7HarOmTHyqKVazZzZ4pnYj
N8dmDttkviZG7hh6641B6Ck7+HAJp0rgvjvlxPKd/zUsVBkNXvYT9CZwwecRIva4
xGbr2XDf7rrAjveduGPKjPv19EJwBBelt8V9lCqkWFVo7hMzk9CxSGIqNmQBEUTv
T/N9AMVvOAyKGZKn484u70fM3TdejPtlyf+lXYWU5ZX2M7Q0dDhQllLBiF8KYKpW
zuO8W2CbXj7YNb7XySnvCfplORJGq2Vo+ddAyTycdxviIRIAJ1RViFS01Um1D9cy
CffymW0CgYEA1opS8cspQHyTTd2eprcScCddmxCFtYZv/0hk/Vgwo9FJq5OnRLRd
CSxhU3Wla3VPkKGf27rdULRPWfu0dUjorcLCyPxvGidTuQef0nvosI2mIBrLtJ4K
hq4rTJ8bDwQTusydfVoff3gYgtBng64o+y3TxUQk7ODn/JFaowDr9FcCgYEAxTaO
cFk63eQUIzXMgIRcV7jq31cRMzVO0XCEH9BUP8U/526TCys3ci3nL+CeQUNrK9pi
U62R1LGKPVgIFNMAjo23xOB7SzyQYCI5l1r80gqKKKx1GH4yCjkw8myZ9+EdoPCh
H13u6dzB6Bbq1z64Pm3tJj9EvCyWpuMCQpCECbsCgYAd9ompDWfAguWLzXT38b+Y
fFb9bixOcu03aSP5ohSA/JzeYqvM06fevR0Gq/qjbGnlWD1cUdfRCq2+coH8k2cz
xWyw51iY/X8a626t1fJknhPijft/SUdNEgwoElyUF0yuHR+tvyWBBwPdWT/ryyoc
EoVuGptRngOoaaCP/XP21wKBgGTwr6dBhKfd/ZCoEKwXE0yzEUSPQ/Z56oW4mWfP
MdASHctPBWRKEm8Wn6YZyeaNo2Umuf0qceHznVYYoMpH1ZkhYFYcr/6qWRtbaS7X
G2BGlMCMxMJslSA2dZ8fhw8g4hFmGJH9ejOpEnbAhCL3r0YE7cUNzRijmdiBiL6Z
SXvRAoGBAKUPhXTuHR0s6JGhQnn++nSlHW39C71/8k5njTvhX0fnvbBWuL9SAsva
VhQf++5F0z93S5Ox+e/JJwlP4DLP5hvj+5Vh2Zx+BHC1vtv1gRg/upxrjk4fO/+/
nucE69OmPtzghGw7O6TML10/WIl1Jy8wDxKmsjQpOnEhAUTtVcTv
-----END RSA PRIVATE KEY-----
)EOF";

const char* AWS_IOT_ENDPOINT = "a6t7fzch59vsw-ats.iot.us-east-1.amazonaws.com";

const int AWS_IOT_PORT = 8883;

