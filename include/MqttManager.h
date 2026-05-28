#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H
#include <Arduino.h>

void configureMQTT();
void connectToMQTT();
void grantMQTTConnection();
void loopMQTT();

void publishMessage(const char *topico, const char *mensagem);
void publicarMensagemNoTopico(int indiceTopico, const char* mensagem);

bool isMQTTConnected();

const char *getPublishedTopic(int indiceTopico);
const char *getTopicoRecebimento(int indiceTopico);

int getTotalTopicosRecebimento();

typedef void (*CallbackMensagemMQTT) (const char *topico, const String& mensagem);

void registerCallbackMessage(CallbackMensagemMQTT callback);

#endif