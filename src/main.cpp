#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionManager.h"

void setup()
{
  configDebug();

  delay(1000);

  Serial.println();
  Serial.println("Iniciando exemplo com ESP32-S3 e Nextion...");

  configurarNextion();
  configurarTelaInicial();
  configurarEventosNextion();

  Serial.println("Sistema iniciado.");
}

void loop()
{
  nexLoop();
}