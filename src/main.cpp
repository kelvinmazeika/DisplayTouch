#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ezTime.h>
#include "ESP32Connectivity.h"

#include "DebugManager.h"
#include "NextionManager.h"
#include "Serialize.h"
#include "secrets.h"
#include "DisplayButtons.h"
#include "QosManager.h"

ConfigAWS aws = {
    AWS_IOT_ENDPOINT,
    AWS_IOT_PORT,
    AWS_IOT_CLIENT_ID,
    AWS_CERT_CA, AWS_CERT_CRT, AWS_CERT_PRIVATE};

ConfigWiFi wifi = {ssid, password};

ConfigTopicos topicos = {
    TOPICOS_PUBLICAR, 6,
    TOPICOS_RECEBER, 3};

void tratarMensagemRecebida(const char *topico, const String &mensagem);

void setup()
{
  configurarDebug();

  conectividade.configurarBufferMQTT(1024);
  conectividade.beginAWS(wifi, aws, topicos);
  conectividade.registrarCallbackMensagem([](const char* topico, const String& msg) {tratarMensagemRecebida(topico, msg);});

  carregarPreferencias();
  configurarNextion();
  configurarTelaInicial();
  configurarEventosNextion();
  iniciaTimestamp();
  delay(1000);

  Serial.println();
  Serial.println("Iniciando exemplo com ESP32-S3 e Nextion...");

  Serial.println("Sistema iniciado.");
}

void loop()
{
  conectividade.update();
  events();
  qosLoop();
  nexLoop();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{

  if (topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }

  if (strcmp(topico, TOPICOS_RECEBER[0]) == 0)
  {
    deserializeModuloAnalise(mensagem);
    return;
  }
  if (strcmp(topico, TOPICOS_RECEBER[1]) == 0)
  {
    deserializeModuloAnaliseB(mensagem);
    return;
  }

  debugErro("Tópico não tratado: " + String(topico));
}
