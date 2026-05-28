//! secrets.
#ifndef SECRETS_H
#define SECRETS_H

extern const char* ssid;
extern const char* password;


//============================
// Debug
//============================
// 0 = sem mensagens
// 1 = apenas erros
// 2 = todas as mensagens
extern const int DEFAULT_DEBUG_LEVEL;

// 4 = Pino utilizado para forçar todas as mensagens na inicialização
extern const int PINO_HABILITA_DEBUG_COMPLETO;

//============================
// Mqtt
//============================

extern const bool USE_AWS_IOT;
 
extern const char* MQTT_BROKER;
extern const int MQTT_PORTA;

extern const char* MQTT_CLIENT_ID;

extern const char* MQTT_USER;
extern const char* MQTT_PASSWORD;

extern const bool MQTT_USE_TLS;

extern const char MQTT_CERTIFICADO_CA[];

extern const char* TOPICOS_PUBLICAR[];

extern const int TOTAL_TOPICOS_PUBLICAR;

extern const char* TOPICOS_RECEBER[];

extern const int TOTAL_TOPICOS_RECEBER;

extern const char AWS_CERT_CA[];

extern const char AWS_CERT_CRT[];

extern const char AWS_CERT_PRIVATE[];

extern const char* AWS_IOT_ENDPOINT;

extern const int AWS_IOT_PORT;

extern const char* AWS_IOT_CLIENT_ID;

#endif
