#include <Arduino.h>
#include <Nextion.h>
#include "NextionManager.h"
#include "DisplayButtons.h"
#include "MqttManager.h"
#include <ArduinoJson.h>

bool projEstadoPower = 0;

bool projEstadoFreeze = 0;

bool telaUp = 0;
bool telaStop = 0;
bool telaDown = 0;

const char TOPICO_COMANDO_PROJETOR[] = "senai/kelvin/esp32/comando";

void publicarComandoProjetorTela(const char *sala, bool comando)
{
    JsonDocument doc;

    if (strcmp(sala, "Up") == 0 || strcmp(sala, "Down") == 0 || strcmp(sala, "Select") == 0) {
        JsonObject tela = doc.createNestedObject("tela");
        tela[sala] = comando ? 1 : 0;
    } else {
        JsonObject projetor = doc.createNestedObject("projetor");
        projetor[sala] = comando ? 1 : 0;
    }

    String mensagem;
    serializeJson(doc, mensagem);
    publishMessage(TOPICO_COMANDO_PROJETOR, mensagem.c_str());
}

void enviarProjetorATelaUp()
{
    publicarComandoProjetorTela("Up", telaUp);
}

void enviarProjetorATelaStop()
{
    publicarComandoProjetorTela("Select", telaStop);
}

void enviarProjetorATelaDown()
{
    publicarComandoProjetorTela("Down", telaDown);
}

void enviarProjetorAPower()
{
    publicarComandoProjetorTela("estadoPower", projEstadoPower);
}

void enviarProjetorAFreeze()
{
    publicarComandoProjetorTela("estadoCongelamento", projEstadoFreeze);
}
