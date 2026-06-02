#include <Serialize.h>
#include <ArduinoJson.h>
#include <MqttManager.h>
#include <DebugManager.h>

void serializarAc()
{
}

void serializeTv(int comando)
{
    String mensagem;
    JsonDocument doc;
    doc["televisao"] = comando;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_TV, mensagem.c_str());
    Serial.printf("\n%s\n", mensagem);
}

void serializeLampada(int sala, bool estadoLampadaTras, bool estadoLampadaFrente)
{
    String mensagem;
    JsonDocument doc;
    if (sala == 9)
    {
        doc["lampadaSala09"]["interruptor1"] = estadoLampadaFrente;
        doc["lampadaSala09"]["interruptor2"] = estadoLampadaTras;
    }
    else if (sala == 10)
    {
        doc["lampadaSala10"]["interruptor3"] = estadoLampadaFrente;
        doc["lampadaSala10"]["interruptor4"] = estadoLampadaTras;
    }

    serializeJson(doc, mensagem);
    debugInfo(mensagem);
    publicarMensagemNoTopico(TOPICO_LAMP, mensagem.c_str());
}
