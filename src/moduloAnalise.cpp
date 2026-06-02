#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <MqttManager.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include "mqtt_client.h"
#include "WiFiManager.h"
#include "DebugManager.h"


void deserializeModuloAnalise(const String &mensagem)
{
 JsonDocument doc; 
 DeserializationError erro = deserializeJson(doc, mensagem);
 
 if(erro)
 {
    debugError("Json inválido, corrigir formatação");
    return;
 }

 if(doc["analise"].is<JsonVariant>())
 {
  if(!doc["analise"]["timestamp"].as<u_long>() || !doc["analise"]["temperatura"].as<float>() || !doc["analise"]["umidade"].as<float>() || doc["analise"]["ruido"].as<float>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["alertaSom"].as<int>() || doc["analise"]["eco"].as<bool>())
    {
     debugError("Json invalido");
     return;
    }
  
 }
 else
 {
  u_long timesTamp = doc["analise"]["timestamp"].as<u_long>();
  float temperatura = doc["analise"]["temperatura"].as<float>();
  float umidade = doc["analise"]["umidade"].as<float>();
  float ruido = doc["analise"]["ruido"].as<float>();
  int comandoAr = doc["analise"]["comandoAr"].as<int>();
  int alerta = doc["analise"]["alertaSom"].as<int>();
  bool eco = doc["analise"]["eco"].as<bool>();
 }
}


