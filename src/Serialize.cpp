#include "Serialize.h"
#include <ArduinoJson.h>
#include "MqttManager.h"
#include "DebugManager.h"
#include "DisplayButtons.h"
#include <ezTime.h>



String mensagemTv;
String mensagemLuz;
String mensagemProj;
String mensagemTela;
String mensagemAC;


void iniciaTimestamp()
{
    setInterval(3600);
    waitForSync();
    tempo.setLocation("America/Sao_Paulo");

}

void serializarAc(int esp, int qualAr, bool estado, int temp, int modo, int vento)
{
    JsonDocument doc;
    doc["ar-condicionado"]["esp"] = esp;
    doc["ar-condicionado"]["id_ar"] = qualAr;
    doc["ar-condicionado"]["estado"] = estado;
    doc["ar-condicionado"]["temperatura"] = temp;
    doc["ar-condicionado"]["modo"] = modo;
    doc["ar-condicionado"]["vento"] = vento;
    doc["timestamp"] = tempo.now();
    serializeJson(doc, mensagemAC);
    //publicarMensagemNoTopico(TOPICO_AC, mensagemAC.c_str());
    debugInfo(mensagemAC);
}

void serializeTv(int comando)
{
    JsonDocument doc;
    doc["televisao"]["comando"] = comando;
    doc["timestamp"] = tempo.now();
    serializeJson(doc, mensagemTv);
    //publicarMensagemNoTopico(TOPICO_TV, mensagemTv.c_str());
    Serial.printf("\n%s\n", mensagemTv);
    Serial.println("Mensagem TV publicada");
}

void serializeLampada(int sala, bool frenteAtras, bool estadoLampada)
{
    JsonDocument doc;
    if (sala == 9)
    {
        if (frenteAtras)
        {
            doc["lampadaSala09"]["interruptor1"] = estadoLampada;
            doc["timestamp"] = tempo.now();
        }
        else
        {
            doc["lampadaSala09"]["interruptor2"] = estadoLampada;
            doc["timestamp"] = tempo.now();
    }
}
    else if (sala == 10)
    {
        if (frenteAtras)
        {
            doc["lampadaSala10"]["interruptor3"] = estadoLampada;
            doc["timestamp"] = tempo.now();
        }
        else
        {
            doc["lampadaSala10"]["interruptor4"] = estadoLampada;
            doc["timestamp"] = tempo.now();
    }
}

    serializeJson(doc, mensagemLuz);
    Serial.printf("\n%s\n", mensagemLuz);
    debugInfo(mensagemLuz);
    //publicarMensagemNoTopico(TOPICO_LAMP, mensagemLuz.c_str());
}

void publicarComandoProjetor(const char *sala, bool power, bool congelamento)
{
    JsonDocument doc;

    JsonObject projetor = doc.createNestedObject("projetor");
    projetor["estadoPower"] = projEstadoPower;
    projetor["estadoCongelamento"] = projEstadoFreeze;

    String mensagem;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_PROJ_09, mensagem.c_str());
}

void enviarProjetor()
{
    publicarComandoProjetor("estadoPower", projEstadoPower, projEstadoFreeze);
}