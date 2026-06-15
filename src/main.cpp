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

ConfigAWS aws = {
    AWS_IOT_ENDPOINT,
    AWS_IOT_PORT,
    AWS_IOT_CLIENT_ID,
    AWS_CERT_CA, AWS_CERT_CRT, AWS_CERT_PRIVATE};

ConfigWiFi wifi = {ssid, password};

ConfigTopicos topicos = {
    TOPICOS_PUBLICAR, TOTAL_TOPICOS_PUBLICAR,
    TOPICOS_RECEBER, TOTAL_TOPICOS_RECEBER};

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
  nexLoop();
}
