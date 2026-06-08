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

void tratarMensagemRecebida(const char* topico, const String& mensagem);

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

  if(strcmp(topico, TOPICOS_RECEBER[0]) == 0)
  {
    deserializeModuloAnalise(mensagem);
    return;
  }
  if(strcmp(topico, TOPICOS_RECEBER[1]) == 0)
  {
    deserializeModuloAnaliseB(mensagem);
    return;
  }

  debugError("Tópico não tratado: " + String(topico));

}
