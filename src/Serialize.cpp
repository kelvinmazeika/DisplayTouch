#include <Serialize.h>
#include <ArduinoJson.h>
#include <MqttManager.h>
#include <DebugManager.h>

String mensagemTv;
String mensagemLuz;

void serializarAc()
{
}

void serializeTv(int comando)
{
    JsonDocument doc;
    doc["televisao"]["comando"] = comando;
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
            doc["lampadaSala09"]["interruptor1"] = estadoLampada;
        else
            doc["lampadaSala09"]["interruptor2"] = estadoLampada;
    }
    else if (sala == 10)
    {
        if (frenteAtras)
            doc["lampadaSala10"]["interruptor3"] = estadoLampada;
        else
            doc["lampadaSala10"]["interruptor4"] = estadoLampada;
    }

    serializeJson(doc, mensagemLuz);
    Serial.printf("\n%s\n", mensagemLuz);
    debugInfo(mensagemLuz);
    //publicarMensagemNoTopico(TOPICO_LAMP, mensagemLuz.c_str());
}
