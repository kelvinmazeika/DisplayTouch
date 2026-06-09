// QosManager.cpp
#include "QosManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

#define QOS_MAX_TENTATIVAS 4
#define QOS_TEMPO_LIMITE 3000

String mensagemTopico = "";
String mensagemPayload = "";
u_long mensagemTimestamp = 0;
int mensagemTentativas = 0;
u_long mensagemUltimoEnvio = 0;
bool mensagemPendente = false;

void qosPublicar(const char *topico, const char *payload, u_long timestamp)
{
    if (mensagemPendente)
    {
        debugError("QoS: ainda aguardando confirmacao da mensagem anterior");
        return;
    }

    mensagemTopico = topico;
    mensagemPayload = payload;
    mensagemTimestamp = timestamp;
    mensagemTentativas = 1;
    mensagemUltimoEnvio = millis();
    mensagemPendente = true;

    publishMessage(topico, payload);
    debugInfo("QoS: enviando (tentativa 1) ts=" + String(timestamp));
}

void qosConfirmar(u_long timestamp)
{
    if (!mensagemPendente)
    {
        debugError("QoS: confirmacao recebida mas nao havia mensagem pendente");
        return;
    }

    if (mensagemTimestamp != timestamp)
    {
        debugError("QoS: timestamp errado, esperava " + String(mensagemTimestamp) +
                   " mas recebeu " + String(timestamp));
        return;
    }

    mensagemPendente = false;
    debugInfo("QoS: confirmado com sucesso ts=" + String(timestamp));
}

void qosLoop()
{
    if (!mensagemPendente)
        return;

    u_long agora = millis();

    if (agora - mensagemUltimoEnvio < QOS_TEMPO_LIMITE)
        return;

    if (mensagemTentativas >= QOS_MAX_TENTATIVAS)
    {
        debugError("QoS: falha apos " + String(QOS_MAX_TENTATIVAS) + " tentativas");
        debugError("QoS: topico=" + mensagemTopico);
        debugError("QoS: payload=" + mensagemPayload);
        mensagemPendente = false;
        return;
    }

    mensagemTentativas++;
    mensagemUltimoEnvio = agora;
    publishMessage(mensagemTopico.c_str(), mensagemPayload.c_str());
    debugInfo("QoS: reenvio (tentativa " + String(mensagemTentativas) +
              ") ts=" + String(mensagemTimestamp));
}

// Feito com ajuda de IA :)