#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ezTime.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionManager.h"
#include "Serialize.h"

void setup()
{
  configDebug();
  
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
  nexLoop();
  events();
}