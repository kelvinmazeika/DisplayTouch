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

void serializeAc(bool estado, int temp, int modo, int vento)
{
    JsonDocument doc;

    for (int i = 0; i < 4; i++)
    {
        if (acSelecionados[i] == 1)
        {
            if (i == 0 || i == 1)
            {
                doc["ar-condicionado"]["esp"] = 0;
                doc["ar-condicionado"]["id_ar"] = i;
            }
            else if (i == 2 || i == 3)
            {
                doc["ar-condicionado"]["esp"] = 1;
                doc["ar-condicionado"]["id_ar"] = i;
            }
            doc["ar-condicionado"]["estado"] = estado;
            doc["ar-condicionado"]["temperatura"] = temp;
            doc["ar-condicionado"]["modo"] = modo;
            doc["ar-condicionado"]["vento"] = vento;
            doc["timestamp"] = tempo.now();
            serializeJson(doc, mensagemAC);
            publicarMensagemNoTopico(TOPICO_AC, mensagemAC.c_str());
            debugInfo(mensagemAC);
        }
    }
}

void serializeTv(int comando)
{
    JsonDocument doc;
    doc["televisao"]["comando"] = comando;
    doc["timestamp"] = tempo.now();
    serializeJson(doc, mensagemTv);
    publicarMensagemNoTopico(TOPICO_TV, mensagemTv.c_str());
    debugInfo(mensagemTv);
}

void serializeLampada(int sala, bool lampadaFrente, int estadoLampada)
{
    JsonDocument doc;
    if (sala == 9)
    {
        if (lampadaFrente)
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
        if (lampadaFrente)
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
    debugInfo(mensagemLuz);
    publicarMensagemNoTopico(TOPICO_LAMP, mensagemLuz.c_str());
}

void onOffTodasLuzes(bool estadoLuzes)
{
    JsonDocument doc;

    if (!luzSalaExtra)
    {

        doc["lampadaSala09"]["interruptor1"] = estadoLuzes;
        doc["timestamp"] = tempo.now();

        doc["lampadaSala09"]["interruptor2"] = estadoLuzes;
        doc["timestamp"] = tempo.now();
    }
    else
    {
        doc["lampadaSala09"]["interruptor1"] = estadoLuzes;
        doc["timestamp"] = tempo.now();

        doc["lampadaSala09"]["interruptor2"] = estadoLuzes;
        doc["timestamp"] = tempo.now();

        doc["lampadaSala10"]["interruptor3"] = estadoLuzes;
        doc["timestamp"] = tempo.now();

        doc["lampadaSala10"]["interruptor4"] = estadoLuzes;
        doc["timestamp"] = tempo.now();
    }

    serializeJson(doc, mensagemLuz);
    debugInfo(mensagemLuz);
}

void serializeProjetor(int power, bool congelamento)
{
    JsonDocument doc;

    for (int i = 0; i < 2; i++)
    {
        if (projetoresSelecionados[i] == 1)
        {
            JsonObject projetor = doc.createNestedObject("projetor");
            projetor["estadoPower"] = power;
            projetor["estadoCongelamento"] = congelamento;
            serializeJson(doc, mensagemProj);
            debugInfo(mensagemProj);
            if (i == 0)
            publicarMensagemNoTopico(TOPICO_PROJ_09, mensagemProj.c_str());
            else if (i == 1)
            publicarMensagemNoTopico(TOPICO_PROJ_10, mensagemProj.c_str());
        }
    }
}

void serializeTelaRetratil(bool up, bool down, bool pause)
{
    JsonDocument doc;

    for(int i = 0; i < 2; i++)
{
    if(projetoresSelecionados[i] == 1)
    {
        doc["telaRetratil"]["tela"] = i;
        doc["telaRetratil"]["UP"] = false;
        doc["telaRetratil"]["PAUSE"] = true;
        doc["telaRetratil"]["DOWN"] = false;
        doc["telaRetratil"]["timestamp"] = tempo.now();
        doc["telaRetratil"]["tempo"] = tempo.dateTime();
    
        serializeJson(doc, mensagemTela);
        publicarMensagemNoTopico(TOPICO_TELA, mensagemTela.c_str());
        debugInfo(mensagemTela);
    }
    }
}