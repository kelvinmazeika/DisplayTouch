#include <Arduino.h>
#include <Nextion.h>
#include "NextionManager.h"
#include "DisplayButtons.h"
#include "MqttManager.h"
#include <ArduinoJson.h>

bool projEstadoPower = 0;

bool projEstadoFreeze = 0;

const char TOPICO_COMANDO_PROJETOR[] = "senai/kelvin/esp32/comando";

void publicarComandoProjetor(const char *sala, bool comando)
{
    JsonDocument doc;

    JsonObject projetor = doc.createNestedObject("projetor");
    projetor["estadoPower"] = projEstadoPower;
    projetor["estadoCongelamento"] = projEstadoFreeze;

    String mensagem;
    serializeJson(doc, mensagem);
    publishMessage(TOPICO_COMANDO_PROJETOR, mensagem.c_str());
}

void enviarProjetor()
{
    publicarComandoProjetor("estadoPower", projEstadoPower);
    publicarComandoProjetor("estadoCongelamento", projEstadoFreeze);
}
