#include "Serialize.h"
#include <ArduinoJson.h>
#include "DebugManager.h"
#include "DisplayButtons.h"
#include <ezTime.h>
#include "secrets.h"
#include <ESP32Connectivity.h>

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
    if (acSelecionados[0] == 1 && acSelecionados[1] == 1 && acSelecionados[2] == 1 && acSelecionados[3] == 1)
    {
        JsonDocument doc;
        doc["ar-condicionado"]["esp"] = 0;
        doc["ar-condicionado"]["estado"] = estado;
        doc["ar-condicionado"]["temperatura"] = temp;
        doc["ar-condicionado"]["modo"] = modo;
        doc["ar-condicionado"]["vento"] = vento;
        doc["timestamp"] = tempo.now();
        serializeJson(doc, mensagemAC);
        conectividade.publicar(TOPICO_AC, mensagemAC.c_str());
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (acSelecionados[i] == 1)
        {
            JsonDocument doc;
            doc["ar-condicionado"]["esp"] = (i < 2) ? 1 : 2;
            doc["ar-condicionado"]["id_ar"] = i;
            doc["ar-condicionado"]["estado"] = estado;
            doc["ar-condicionado"]["temperatura"] = temp;
            doc["ar-condicionado"]["modo"] = modo;
            doc["ar-condicionado"]["vento"] = vento;
            doc["timestamp"] = tempo.now();
            serializeJson(doc, mensagemAC);
            conectividade.publicar(TOPICO_AC, mensagemAC.c_str());
            debugInfo(mensagemAC);
        }
    }
}

void serializeTv(int comando)
{
    JsonDocument doc;
    doc["televisao"]["comando"] = comando;
    doc["televisao"]["timestamp"] = tempo.now();
    serializeJson(doc, mensagemTv);
    conectividade.publicar(TOPICO_TV, mensagemTv.c_str());
    debugInfo(mensagemTv);
}

void serializeLampada(int sala, bool lampadaFrente, int estadoLampada)
{
    JsonDocument doc;
    if (sala == 9)
    {
        if (lampadaFrente)
            doc["lampadaSala09"]["interruptor1"] = estadoLampada;
        else
            doc["lampadaSala09"]["interruptor2"] = estadoLampada;
    }
    else if (sala == 10)
    {
        if (lampadaFrente)
            doc["lampadaSala10"]["interruptor3"] = estadoLampada;
        else
            doc["lampadaSala10"]["interruptor4"] = estadoLampada;
    }
    doc["timestamp"] = tempo.now();
    serializeJson(doc, mensagemLuz);
    conectividade.publicar(TOPICO_LAMP, mensagemLuz.c_str());
    debugInfo(mensagemLuz);
}

void onOffTodasLuzes(bool estadoLuzes)
{
    JsonDocument doc;
    doc["lampadaSala09"]["interruptor1"] = estadoLuzes;
    doc["lampadaSala09"]["interruptor2"] = estadoLuzes;
    if (luzSalaExtra)
    {
        doc["lampadaSala10"]["interruptor3"] = estadoLuzes;
        doc["lampadaSala10"]["interruptor4"] = estadoLuzes;
    }
    doc["timestamp"] = tempo.now();
    serializeJson(doc, mensagemLuz);
    conectividade.publicar(TOPICO_LAMP, mensagemLuz.c_str());
    debugInfo(mensagemLuz);
}

void serializeProjetor(int power, int congelamento)
{
    JsonDocument doc;
    doc["projetor"]["estadoPower"] = power;
    doc["projetor"]["estadoCongelamento"] = congelamento;
    serializeJson(doc, mensagemProj);
    debugInfo(mensagemProj);

    if (projSalaExtra)
    {
        for (int i = 0; i < 2; i++)
        {
            if (projetoresSelecionados[i] == 1)
            {

                if (i == 0)
                    conectividade.publicar(TOPICO_PROJ_09, mensagemProj.c_str());
                else
                    conectividade.publicar(TOPICO_PROJ_10, mensagemProj.c_str());
            }
        }
    }
    else
    {
        conectividade.publicar(TOPICO_PROJ_09, mensagemProj.c_str());
    }
}

void serializeTelaRetratil(bool up, bool down, bool pause)
{
    if (projSalaExtra)
    {
        for (int i = 0; i < 2; i++)
        {
            if (projetoresSelecionados[i] == 1)
            {
                JsonDocument doc;
                doc["telaRetratil"]["tela"] = i;
                doc["telaRetratil"]["UP"] = up;
                doc["telaRetratil"]["PAUSE"] = pause;
                doc["telaRetratil"]["DOWN"] = down;
                doc["telaRetratil"]["timestamp"] = tempo.now();
                doc["telaRetratil"]["tempo"] = tempo.dateTime();
                serializeJson(doc, mensagemTela);
                conectividade.publicar(TOPICO_TELA, mensagemTela.c_str());
                debugInfo(mensagemTela);
            }
        }
    }
    else
    {
        JsonDocument doc;
        doc["telaRetratil"]["tela"] = 0;
        doc["telaRetratil"]["UP"] = up;
        doc["telaRetratil"]["PAUSE"] = pause;
        doc["telaRetratil"]["DOWN"] = down;
        doc["telaRetratil"]["timestamp"] = tempo.now();
        doc["telaRetratil"]["tempo"] = tempo.dateTime();
        serializeJson(doc, mensagemTela);
        conectividade.publicar(TOPICO_TELA, mensagemTela.c_str());
        debugInfo(mensagemTela);
    }
}