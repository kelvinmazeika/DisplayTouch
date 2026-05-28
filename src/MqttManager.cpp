#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "WiFiManager.h"
#include "secrets.h"
#include "DebugManager.h"
#include <PubSubClient.h>
#include "MqttManager.h"

// Instancias
WiFiClient wifiClient;
WiFiClientSecure wifiClientSecure;
PubSubClient mqttClient;

CallbackMensagemMQTT callbackDaAplicacao = nullptr;

void registerCallbackMessage(CallbackMensagemMQTT callback)
{
    callbackDaAplicacao = callback;

    if (callbackDaAplicacao != nullptr)
    {
        debugInfo("Callback da aplicação registrada com sucesso");
    }
    else
    {
        debugError("Callback da aplicação não foi registrada.");
    }
}

const char *getPublishedTopic(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_PUBLICAR)
    {
        debugError("Índice inválido para tópico de publicação: " + String(indiceTopico));
        return "";
    }

    return TOPICOS_PUBLICAR[indiceTopico];
}

const char *getTopicoRecebimento(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_RECEBER)
    {
        debugError("Índice inválido para tópico de recebimento: " + String(indiceTopico));
        return "";
    }

    return TOPICOS_RECEBER[indiceTopico];
}
void callbackInternoMQTT(char *topico, byte *payload, unsigned int tamanho)
{
    String mensagem = "";
    for (unsigned int i = 0; i < tamanho; i++)
    {
        mensagem += (char)payload[i];
    }
    debugInfo("========================");
    debugInfo(" Mensagem MQTT recebida!");
    debugInfo("========================");
    debugInfo("Tópico: " + String(topico));
    debugInfo("Mensagem: " + mensagem);

    if (callbackDaAplicacao != nullptr)
    {
        callbackDaAplicacao(topico, mensagem);
    }
    else
    {
        debugError("Mensagem foi recebida porém nenhum callback da aplicação foi registrado.");
    }
}

void configureMQTT()
{

    debugInfo("========================");
    debugInfo(" Configurando o MQTT...");
    debugInfo("========================");

    if (USE_AWS_IOT)
    {
       debugInfo("Modo selecionado: AWS IoT Core");
       debugInfo("Configurando certificados da AWS IoT Core");
       wifiClientSecure.setCACert(AWS_CERT_CA);
       wifiClientSecure.setCertificate(AWS_CERT_CRT);
       wifiClientSecure.setPrivateKey(AWS_CERT_PRIVATE);

       mqttClient.setClient(wifiClientSecure);
       mqttClient.setServer(AWS_IOT_ENDPOINT, AWS_IOT_PORT);
       debugInfo("Endpoint AWS IoT : " + String(AWS_IOT_ENDPOINT));
       debugInfo("Porta AWS IoT : " + String(AWS_IOT_PORT));
    }

    else if (MQTT_USE_TLS)
    {
        debugInfo("Modo selecionado: MQTT com TLS.");

        if(strlen(MQTT_CERTIFICADO_CA) > 100)
        {
            debugInfo("Certificado CA do broker MQTT configurado.");
            wifiClientSecure.setCACert(MQTT_CERTIFICADO_CA);
        }

        else
        {
            debugError("Certificado Ca do MQTT não configurado. Usando setInsecure apenas para teste");
            wifiClientSecure.setInsecure();
        }
        mqttClient.setClient(wifiClientSecure);
        mqttClient.setServer(MQTT_BROKER, MQTT_PORTA);
    
        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_PORTA));
    }

    else // conectar no broker sem certificado
    {
        debugInfo("Modo selecionado: MQTT sem TLS.");
        mqttClient.setClient(wifiClient);
        mqttClient.setServer(MQTT_BROKER, MQTT_PORTA);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_PORTA));
    }

    mqttClient.setCallback(callbackInternoMQTT);
    debugInfo(" Callback interno do MQTT configurado.");
}

void connectToMQTT()
{
    if (!wifiIsConnected())
    {
        debugError("MQTT não pode conectar porque o WiFi está desconectado.");
        return;
    }

    debugInfo("==========================");
    debugInfo(" Inciando conexão MQTT...");
    debugInfo("==========================");

    int tentativasMQTT = 0;
    const int maxTentativasMQTT = 5;

    while (!mqttClient.connected() && tentativasMQTT < maxTentativasMQTT)
    {
        debugInfo("Tentando conectar ao Broker MQTT. Tentativa: " + String(tentativasMQTT));

        bool conectado = false;

        if (USE_AWS_IOT)
        {
            conectado = mqttClient.connect(AWS_IOT_CLIENT_ID);
        }
        else
        {
            if (strlen(MQTT_USER) > 0)
            {
                debugInfo("Conectando MQTT com o usuário e senha");

                conectado = mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD);
            }
            else // Sem usuário
            {
                debugInfo("Conectando MQTT sem usuário e senha.");

                conectado = mqttClient.connect(MQTT_CLIENT_ID);
            }
        }
        if (conectado)
        {
            debugInfo("MQTT conectado com sucesso.");

            int totalTopicos = getTotalTopicosRecebimento();

            debugInfo("Total de tópicos para inscrição: " + String(totalTopicos));

            for (int i = 0; i < totalTopicos; i++)
            {
                const char *topico = getTopicoRecebimento(i);

                bool inscrito = mqttClient.subscribe(topico);

                if (inscrito)
                {
                    debugInfo("Inscrito no tópico: " + String(topico));
                }
                else
                {
                    debugError("Falha ao se inscrever no tópico: " + String(topico));
                }
            }
            //TODO: publicar uma mensagem em um tópico informando que o esp foi conectado.
        }
        else
        {
            debugError("Falha ao conectar ao MQTT, Código de erro: " + String(mqttClient.state() ));

            tentativasMQTT++;
            delay(2000);
        }
    } // fim do while

    if(!mqttClient.connected())
    {
        debugError("Não foi possível conectar ao broker MQTT após " + String(maxTentativasMQTT) + " tentativas");
    }
}

void grantMQTTConnection()
{
    if(!wifiIsConnected())
    {
        debugError("MQTT não será reconectado porque o WiFi está desconectado.");
        return;
    }

    if(!mqttClient.connected())
    {
        debugError("MQTT desconectado. Tentando reconectar...");
        connectToMQTT();
    }
}

void loopMQTT()
{
    mqttClient.loop();
}

void publishMessage(const char *topico, const char *mensagem)
{
    if(!mqttClient.connected())
    {
        debugError("Não foi possível publicar. MQTT desconectado.");
        return;
    }

    bool publicado = mqttClient.publish(topico, mensagem);

    if(publicado)
    {
        debugInfo("Mensagem publicada via MQTT.");
        debugInfo("Tópico: " + String(topico));
        debugInfo("Mensagem: " + String(mensagem));
    } else
    {
        debugError("Falha ao publicar mensagem no tópico: " + String(topico));
    }

    
}

void publicarMensagemNoTopico(int indiceTopico, const char* mensagem)
{
    const char* topico = getPublishedTopic(indiceTopico);

    if(strlen(topico) == 0)
    {
        debugError("Não foi possível publicar. Índice de tópico inválido: " + String(indiceTopico));
        return;
    }
    publishMessage(topico, mensagem);


}

bool isMQTTConnected()
{
    return mqttClient.connected();
}

int getTotalTopicosRecebimento()
{
    return TOTAL_TOPICOS_PUBLICAR;
}