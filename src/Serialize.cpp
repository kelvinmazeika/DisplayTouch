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

void serializeAc(int estado, int temp, int modo, int vento)
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
            doc["ar-condicionado"]["id_ar"] = i + 1;
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
    doc["comando"] = comando;
    doc["timestamp"] = tempo.now();
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

void onOffTodasLuzes(int estadoLuzes)
{
    JsonDocument doc;
    doc["lampadaSala09"]["interruptor1"] = estadoLuzes;
    doc["lampadaSala09"]["interruptor2"] = estadoLuzes;
    doc["lampadaSala09"]["timestamp"] = tempo.now();
    if (luzSalaExtra)
    {
        doc["lampadaSala10"]["interruptor3"] = estadoLuzes;
        doc["lampadaSala10"]["interruptor4"] = estadoLuzes;
        doc["lampadaSala10"]["timestamp"] = tempo.now();
    }
    serializeJson(doc, mensagemLuz);
    conectividade.publicar(TOPICO_LAMP, mensagemLuz.c_str());
    debugInfo(mensagemLuz);
}

void serializeProjetor(int acao)
{
    JsonDocument doc;
    if(acao == 0)
    doc["power"] = 0;
    else if(acao == 1)
    doc["power"] = 1;
    else if(acao == 2)
    doc["freeze"] = 0;
    else if(acao == 3)
    doc["freeze"] = 1;
    doc["timestamp"] = tempo.now();
    debugInfo(mensagemProj);
    
    if (projSalaExtra)
    {
        for (int i = 0; i < 2; i++)
        {
            if (projetoresSelecionados[i] == 1)
            {
                doc["id"] = i+1;
                serializeJson(doc, mensagemProj);
                conectividade.publicar(TOPICO_PROJ, mensagemProj.c_str());
            }
        }
        return;
    }
    else
    {
        doc["id"] = 1;
        serializeJson(doc, mensagemProj);
        conectividade.publicar(TOPICO_PROJ, mensagemProj.c_str());
    }
}

void serializeTelaRetratil(int acao)
{
    if (projSalaExtra)
    {
        for (int i = 0; i < 2; i++)
        {
            if (projetoresSelecionados[i] == 1)
            {
                JsonDocument doc;
                doc["telaRetratil"]["tela"] = i;
                if(acao == 0)
                doc["telaRetratil"]["comando"] = 0;
                else if(acao == 1)
                doc["telaRetratil"]["comando"] = 1;
                else if(acao == 2)
                doc["telaRetratil"]["comando"] = 2;
                doc["telaRetratil"]["timestamp"] = tempo.now();
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
        if(acao == 0)
                doc["telaRetratil"]["comando"] = 0;
                else if(acao == 1)
                doc["telaRetratil"]["comando"] = 1;
                else if(acao == 2)
                doc["comando"] = 2;
        doc["telaRetratil"]["timestamp"] = tempo.now();
        serializeJson(doc, mensagemTela);
        conectividade.publicar(TOPICO_TELA, mensagemTela.c_str());
        debugInfo(mensagemTela);
    }
}