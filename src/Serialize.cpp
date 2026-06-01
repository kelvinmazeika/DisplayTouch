#include <Serialize.h>
#include <ArduinoJson.h>
#include <MqttManager.h>

const char* TOPICO_TV_A = "senai/projeto/tv/a";

void serializarAc()
{

}

void serializeTv(int acao)
{
    String mensagem; 
    JsonDocument doc;
    doc["televisao"] = acao;
    serializeJson(doc, mensagem);
    publishMessage(TOPICO_TV_A, mensagem.c_str());
    Serial.printf("\n%s\n", mensagem);
}