#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ezTime.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionManager.h"
#include "Serialize.h"
#include "secrets.h"

void tratarMensagemRecebida(const char *topico, const String &mensagem);

void setup()
{
  configDebug();

  connectToWifi();
  configureMQTT();
  registerCallbackMessage(tratarMensagemRecebida);
  connectToMQTT();

  configurarNextion();
  configurarTelaInicial();
  configurarEventosNextion();
  //iniciaTimestamp();
  delay(1000);

  Serial.println();
  Serial.println("Iniciando exemplo com ESP32-S3 e Nextion...");

  Serial.println("Sistema iniciado.");
}

void loop()
{
  grantMQTTConnection();
  grantWiFiAccess();
  nexLoop();
  //events();
}

void tratarMensagemRecebida(const char* topico, const String& mensagem)
{
  debugInfo("==============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("==============================");
  
  if(topico == nullptr)
  {
    debugError("Tópico MQTT inválido");
    return;
  }
  
  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

<<<<<<< HEAD
  if(strcmp(topico, TOPICOS_RECEBER[TOPICO_ANALISE_09]) == 0 || strcmp(topico, TOPICOS_RECEBER[TOPICO_ANALISE_10]) == 0)
=======
  if(strcmp(topico, "senai134/shared/projeto/analise09") == 0)
>>>>>>> 308464108ca130d1c0711e4d5d3ad8c53f054dde
  {
    deserializeModuloAnalise(mensagem);
    return;
  }

  debugError("Tópico não tratado: " + String(topico));

}
