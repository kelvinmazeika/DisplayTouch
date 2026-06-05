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


const char* MQTT_BROKER = "a3cxr9ayydc4np-ats.iot.us-east-1.amazonaws.com";
const int MQTT_PORTA = 8883;

const char* MQTT_CLIENT_ID = "wario-analise";

const char* MQTT_USER = "kelvin";
const char* MQTT_PASSWORD = "Senai@134";

const bool MQTT_USE_TLS = false;

const char MQTT_CERTIFICADO_CA[] PROGMEM = R"EOF()EOF";

//============================
// TOPICOS
//============================

const char* TOPICOS_PUBLICAR[] = 
{
    "senai134/shared/projeto/TV",
    "senai134/shared/projeto/AC",
    "senai134/shared/projeto/telaRetratil",
    "senai134/shared/projeto/projetor09",
    "senai134/shared/projeto/projetor10"
};

const int TOTAL_TOPICOS_PUBLICAR = sizeof(TOPICOS_PUBLICAR) / sizeof(TOPICOS_PUBLICAR[0]);

const char* TOPICOS_RECEBER[] =
{
    "senai134/shared/projeto/analise09",
    "senai134/shared/projeto/analise10",
    "senai134/shared/projeto/status"
};

const int TOTAL_TOPICOS_RECEBER = sizeof(TOPICOS_RECEBER) / sizeof(TOPICOS_RECEBER[0]);

//============================
// AWS
//============================

const bool USE_AWS_IOT = true;

const char* AWS_IOT_CLIENT_ID = "wario-13446";

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
MIIDWTCCAkGgAwIBAgIUQEjBsoOieV8ly256I+ikppJQXE8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUyMDIwMDMx
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKeQRe9e8qLgoVXG1BhU
pfbUizV2SRWU8+qR14pnteGtiUdsvd7hQv5NPXgu177TFR+4hlnas1NiJdsw9AOb
31MHywWxW2iYKxx2BEUhzOhPF+UPIBAJro+HE8F+mKQPyR37hRlxCqnftIJ7woXs
h/f5GmZ93OvP9f0CII8sar4SbgIrnuys88qQPXDyby4PXlpHdgZzdjQOwxZVFkKU
wj8fZY12v/RUKnTxetn6Tbc9C1rm9KdvrK9wNOmdGX1xYNPeRI7g+kMWTdcksgE3
/cim4MPHhUs8eW17NbxcVwxwKbRrnVaWXib/xjhszuA/JOGsWcmA8ggKIiM48w2n
VzkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUBIVpP1/0DIPQ8KV5+xNpiljTfT8wHQYD
VR0OBBYEFCSZpl6F5tMGme/I4Mnpzv5vdhVaMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAGZpsuVMfRNXTwVJthVa6NVVSU
94JLNCVhSpmjJ/Qn2fbOgJzBQlY17KHFuworJbjenRsGKsnu+ZymyM0N6sPuT8uI
z6MheTv6ZV/pPvt1DoJGeECD/Mz+95g2mYzwGsb3mFS7Phjq6+aQ/V2T+y1YMNk9
UrtC55FGKro1qZMFEburFFDk3OCUC9DXvZKTsbqREP/VAgsfVj7/64zEmKj8RNY3
WQj+2uP2SIWz8JdpHBfYdiwSb7xE0Vj0JykrX2rzfB7zfO0Ms7FxZ4CRx1EM2jCE
LO2trrt/i7SXrj4vH2y1Sfp4yEAqIkkhYQLKp4cjzgxOtD7orzgZx6Ship6/
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAp5BF717youChVcbUGFSl9tSLNXZJFZTz6pHXime14a2JR2y9
3uFC/k09eC7XvtMVH7iGWdqzU2Il2zD0A5vfUwfLBbFbaJgrHHYERSHM6E8X5Q8g
EAmuj4cTwX6YpA/JHfuFGXEKqd+0gnvCheyH9/kaZn3c68/1/QIgjyxqvhJuAiue
7KzzypA9cPJvLg9eWkd2BnN2NA7DFlUWQpTCPx9ljXa/9FQqdPF62fpNtz0LWub0
p2+sr3A06Z0ZfXFg095EjuD6QxZN1ySyATf9yKbgw8eFSzx5bXs1vFxXDHAptGud
VpZeJv/GOGzO4D8k4axZyYDyCAoiIzjzDadXOQIDAQABAoIBADcmUv4/39gf2rni
oPgJFD6zIcZM0i0aQ1WW/rv8+m32sdIiRjPPLD+KqIqf0D5sNu2jzARS6OauzQrh
h86QROaNEBMllpJMUxQg+7LNNyXWsmSfn8vng96VdLkgs5h74ZPOrrX68KmMiVrQ
5OszOGUzRa8qCcZLQgkt5A17bv5zhg36BHHHsMtVHVBAQRJ5WRKfD9wMxGj8VK2E
A4bpk/SKtwF/iZ0vwQ+eznpAhYm+C/41dvr0YJzNnMR+7KyMXOjkSOcnc/nPQ0v+
N9LN8kF+vnMqATZZ9YBdL/zllz3kFg9CY6AYiuyT/Zgx0htzhsP5Q/KjMx0KNzG8
h3BaSUkCgYEA0Ruy+RZLXCFDs9sHe37ahiAdJPwjxjpTN8uv227+rAKF2R4sp+Xp
uS7reRZuxXD8tSt7bU8E5Bc31wORxWFW7oltR+/gK/MbzQp2yepIgVCuSI+atUVd
7WOqAfw+U+wbi+pr+pjKjQxdaIV5ppm2RM+G0yvEg2XhDM4ShGzGwTMCgYEAzSOd
uDAy/ZMPDUKtq/2y2CHzyagnF5zdrnKJ323otDPtjtp0PLJ3qS5J0kcnLRlGdr+4
wPMFjUM9f77uDB9qBKjyVJJ3STS20RX1zqG5/rHURzEPZfyrWUkXSthhkKyZN0c0
RezdLhE5QgspiNI6tTVZAvlGWF2X3A59RUrb3eMCgYBLo3NXuoLD7pxowH+yYi51
ecRRDot6NrrHYfxYqYuheMAly05n5Thn7drrT/v9m2MtvW7GGWExiFyAgCAIf69M
VZWcAd7axvN1daWGYCKd9Cs2wAs8Kr1RE035rd51yOAl+kPYv8/0uVZIao+Yfd16
gn7If/pzdTS0xw3XrOkwFQKBgQDDlTWGqs2y3kb3iZ8z4Apn7tcUaPH8nV7uN94j
3BKF3QydqsIwLKfR8YQIrDY51WNNTLXFoO6mJHm6Fju36yuVjc6du5dngI7dAmb9
v0wp/To7NhdMUX68/ebrQSqkWSsrfQPlt1OZ3GoPAb1z6Zx3sIlRQIFFNtbWxCnD
qv+9qQKBgQCqjIrcy0wS8vizM4hGN3h1FqKJPyjxpL57IVJOXrjE1IwoOLZx3UMQ
7lDYgxY+6tQ0EjDrbtsPaVhn/EZukJupmblwpDAWydT7SUjnwAOsIxxSiLI06bg6
whX+qxmWrzy0r0ZQsJmkT1fehtxcylk5g9wmLCj7Lb/yQuwLq3q+5Q==
-----END RSA PRIVATE KEY-----
)EOF";

const char* AWS_IOT_ENDPOINT = "a3cxr9ayydc4np-ats.iot.us-east-1.amazonaws.com";

const int AWS_IOT_PORT = 8883;

