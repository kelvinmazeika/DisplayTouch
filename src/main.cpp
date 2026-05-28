#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <Nextion.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionManager.h"

const uint8_t PINO_LED_RGB = 48;
const uint8_t QUANTIDADE_LEDS = 1;
const uint8_t pinLampada = 38;

const char TOPICO_COMANDO[] = "senai/kelvin/esp32/comando";

Adafruit_NeoPixel ledRGB(
    QUANTIDADE_LEDS,
    PINO_LED_RGB,
    NEO_GRB + NEO_KHZ800 // Duas constantes que definem a saidas do rgb e a frquencia de propagacao da informacao entre os LED`s, nesse caso é igual a 82
);

void configuraLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonComando(const String &mensagem);
void updateLampada(bool estado);

void tratarMensagemRecebida(const char *topico, const String &mensagem);

void setup()
{
  configDebug();
  pinMode(pinLampada, OUTPUT);

  configuraLedRGB();

  connectToWifi();
  configureMQTT();
  registerCallbackMessage(tratarMensagemRecebida);
  connectToMQTT();

  delay(1000);
  configurarNextion();
  configurarTelaInicial();
  configurarEventosNextion();
}

void loop()
{
  grantWiFiAccess();
  grantMQTTConnection();
  loopMQTT();
  nexLoop();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{
  debugInfo("==============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("==============================");

  if (topico == nullptr)
  {
    debugError("Tópico MQTT inválido");
    return;
  }

  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  if (strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }

  debugError("Tópico não tratado: " + String(topico));
}

void configuraLedRGB()
{
  ledRGB.begin();
  ledRGB.setBrightness(80); // Colocamos a qtd de brilho para o led de 0 a 255
  ledRGB.clear();
  ledRGB.show(); // atualiza estado led
}

void alterarCorLedRGB(int vermelho, int verde, int azul)
{
  vermelho = constrain(vermelho, 0, 255);
  verde = constrain(verde, 0, 255);
  azul = constrain(azul, 0, 255);

  ledRGB.setPixelColor(0, ledRGB.Color(vermelho, verde, azul));
  ledRGB.show();

  debugInfo("Cor aplicada o LED RGB");
  debugInfo("R: " + String(vermelho));
  debugInfo("G: " + String(verde));
  debugInfo("B: " + String(azul));
}

void updateLampada(bool estado)
{
  digitalWrite(pinLampada, estado);
}

void tratarJsonComando(const String &mensagem)
{
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, mensagem);

  if (error)
  {
    debugError("Erro ao interpretar JSON.");
    debugError(error.c_str());
    return;
  }

  if (!doc["led"].is<JsonObject>() && !doc["lampada"].is<JsonObject>())
  {
    if (!doc["led"]["r"].is<int>() || !doc["led"]["g"].is<int>() || !doc["led"]["b"].is<int>() || !doc["led"].is<bool>())
    {
      debugError("JSON Inválido. Use led.r, led.g e led.b e lampada");
      return;
    }
  }

  else
  {
    int vermelho = doc["led"]["r"].as<int>();
    int verde = doc["led"]["g"].as<int>();
    int azul = doc["led"]["b"].as<int>();
    bool lampada = doc["lampada"].as<bool>();

    updateLampada(lampada);
    alterarCorLedRGB(vermelho, verde, azul);
  }
}