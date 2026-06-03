#include <Arduino.h>
#include <Nextion.h>
#include "DisplayButtons.h"
#include "NextionManager.h"
#include "Serialize.h"
#include <ArduinoJson.h>
#include <DebugManager.h>

// =========================================================
// CONFIGURAÇÃO DA COMUNICAÇÃO COM O NEXTION
// =========================================================

bool luzSalaExtra = 0;
bool arSalaExtra = 0;
bool projSalaExtra = 0;
bool tvSalaExtra = 0;
uint8_t acaoTv;

bool estadoLuzes[2][2] = {{0, 0}, {0, 0}};
bool estadoTv[2] = {0, 0};

float temperatura;
float umidade;
float ruido;
int comandoAr;
int alerta;
bool eco;
u_long timeStampAnalise;
char buffer[100];

// Velocidade padrão de comunicação serial do Nextion
const uint32_t BAUD_NEXTION = 9600;

// RX do ESP32-S3 ligado ao TX do Nextion
const int8_t PINO_RX_NEXTION = 18;

// TX do ESP32-S3 ligado ao RX do Nextion
const int8_t PINO_TX_NEXTION = 17;

// Buffer usado para montar textos antes de enviar ao display
char texto[50];

// =========================================================
// PROTÓTIPOS DAS FUNÇÕES
// =========================================================

void configurarNextion()
{
    Serial.println("Chamando nextion agora");
    // Inicializa a comunicação serial com o display Nextion.
    // Parâmetros:
    // 1. baud rate
    // 2. pino RX do ESP32-S3
    // 3. pino TX do ESP32-S3
    bool nextionOk = nexInit(BAUD_NEXTION, PINO_RX_NEXTION, PINO_TX_NEXTION);
    if (!nextionOk)
    {
        Serial.println("Aviso: o Nextion nao confirmou a inicializacao.");
    }
    else
    {
        Serial.println("Nextion inicializado.");
    }
}

void configurarTelaInicial()
{
    sendCommand("page inicial");
    delay(500);
    sendCommand("bkcmd=3");
    delay(100);
}

void configurarEventosNextion()
{
    botaoBackLuz1.attachPop([](){ updateTela(10); }); // "LAMBDA", muito maneiro vale a pena pesquisar sobre isso
    botaoBackLuz2.attachPop([](){ updateTela(10); });
    botaoBackAc1.attachPop([](){ updateTela(10); });
    botaoBackAc2.attachPop([](){ updateTela(10); });
    botaoBackAc3.attachPop([](){ updateTela(10); });
    botaoBackProj1.attachPop([](){ updateTela(10); });
    botaoBackProj2.attachPop([](){ updateTela(10); });
    botaoBackTv1.attachPop([](){ updateTela(10); });
    botaoBackTv2.attachPop([](){ updateTela(10); });
    botaoBackTv3.attachPop([](){ updateTela(10); });

    botaoLuz.attachPop([](){ updateTela(0); });
    botaoAr.attachPop([](){ updateTela(1); });
    botaoProj.attachPop([](){ updateTela(2); });
    botaoTv.attachPop([](){ updateTela(3); });
    botaoSens.attachPop([](){ updateTela(4); });
    botaoSettings.attachPop([](){ updateTela(5); });

    adicionarSalaExtraLuz.attachPop([](){ addSalaExtra(0); });
    adicionarSalaExtraAc.attachPop([](){ addSalaExtra(1); });
    adicionarSalaExtraProj.attachPop([](){ addSalaExtra(2); });
    adicionarSalaExtraTv.attachPop([](){ addSalaExtra(3); });

    removerSalaExtraLuz.attachPop([](){ removeSalaExtra(0); });
    removerSalaExtraAc.attachPop([](){ removeSalaExtra(1); });
    removerSalaExtraAc3.attachPop([](){ removeSalaExtra(1); });
    removerSalaExtraProj.attachPop([](){ removeSalaExtra(2); });
    removerSalaExtraTv.attachPop([](){ removeSalaExtra(3); });
    removerSalaExtraTv2.attachPop([](){ removeSalaExtra(3); });

    // Tela Sala Extra AC
    pageAc2.attachPop([](){ updateTela(7); });
    pageAc3.attachPop([](){ updateTela(6); });

    // Tela Sala Extra TV
    tvPageB2.attachPop([](){ updateTela(9); });
    tvPageA3.attachPop([](){ updateTela(8); });

    botaoLuzA.attachPop([](){
    estadoLuzes[0][1] = !estadoLuzes[0][1];
    onOffLuz(9, 1, estadoLuzes[0][1]); });
    botaoLuzB.attachPop([](){
    estadoLuzes[0][0] = !estadoLuzes[0][0];
     onOffLuz(9, 0, estadoLuzes[0][0]); });
    
    botaoLuzA2.attachPop([](){ 
    estadoLuzes[0][1] = !estadoLuzes[0][1];
     onOffLuz(9, 1, estadoLuzes[0][1]); });
    botaoLuzB2.attachPop([](){
    estadoLuzes[0][0] = !estadoLuzes[0][0];
     onOffLuz(9, 0, estadoLuzes[0][0]); });
    botaoLuzC2.attachPop([](){
    estadoLuzes[1][0] = !estadoLuzes[1][0];
     onOffLuz(10, 1, estadoLuzes[1][0]); });
    botaoLuzD2.attachPop([](){ 
    estadoLuzes[1][1] = !estadoLuzes[1][1];
     onOffLuz(10, 0, estadoLuzes[1][1]); });


    tvAOn.attachPop([]() { 
        estadoTv[0] = !estadoTv[0];
        serializeTv(estadoTv[0]);
    });
    tvAOn2.attachPop([]() { 
        estadoTv[0] = !estadoTv[0];
        serializeTv(estadoTv[0]);
    });
    tvBOn3.attachPop([]() { 
        estadoTv[1] = !estadoTv[1];
        serializeTv(estadoTv[1]);
    });
    


    nexListen(botaoBackLuz1);
    nexListen(botaoBackLuz2);
    nexListen(botaoBackAc1);
    nexListen(botaoBackAc2);
    nexListen(botaoBackAc3);
    nexListen(botaoBackProj1);
    nexListen(botaoBackProj2);
    nexListen(botaoBackTv1);
    nexListen(botaoBackTv2);
    nexListen(botaoBackTv3);

    nexListen(adicionarSalaExtraAc);
    nexListen(adicionarSalaExtraLuz);
    nexListen(adicionarSalaExtraProj);
    nexListen(adicionarSalaExtraTv);

    nexListen(removerSalaExtraLuz);
    nexListen(removerSalaExtraAc);
    nexListen(removerSalaExtraAc3);
    nexListen(removerSalaExtraProj);
    nexListen(removerSalaExtraTv);
    nexListen(removerSalaExtraTv2);

    nexListen(botaoLuz);
    nexListen(botaoAr);
    nexListen(botaoProj);
    nexListen(botaoTv);
    nexListen(botaoSens);
    nexListen(botaoSettings);

    nexListen(pageAc2);
    nexListen(pageAc3);

    nexListen(tvPageB2);
    nexListen(tvPageA3);

    nexListen(botaoLuzA);
    nexListen(botaoLuzB);

    nexListen(botaoLuzA2);
    nexListen(botaoLuzB2);
    nexListen(botaoLuzC2);
    nexListen(botaoLuzD2);
}

void updateTela(int modulo)
{
    switch (modulo)
    {
    case 0:
        if (luzSalaExtra)
            sendCommand("page luz2");
        else
            sendCommand("page luz1");
        break;
    case 1:
        if (arSalaExtra)
            sendCommand("page ac2");
        else
            sendCommand("page ac1");
        break;
    case 2:
        if (projSalaExtra)
            sendCommand("page proj2");
        else
            sendCommand("page proj1");
        break;
    case 3:
        if (tvSalaExtra)
            sendCommand("page tv2");
        else
            sendCommand("page tv1");
        break;
    case 4:
        sendCommand("page sens");
        break;
    case 5:
        sendCommand("page settings");
        break;
    case 6:
        sendCommand("page ac2");
        break;
    case 7:
        sendCommand("page ac3");
        break;
    case 8:
        sendCommand("page tv2");
        break;
    case 9:
        sendCommand("page tv3");
        break;
    case 10:
        sendCommand("page inicial");
        break;
    }
}

void addSalaExtra(int modulo)
{
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 1;
        updateTela(0);
        break;
    case 1:
        arSalaExtra = 1;
        updateTela(1);
        break;
    case 2:
        projSalaExtra = 1;
        updateTela(2);
        break;
    case 3:
        tvSalaExtra = 1;
        updateTela(3);
        break;
    }
}

void removeSalaExtra(int modulo)
{
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 0;
        updateTela(0);
        break;
    case 1:
        arSalaExtra = 0;
        updateTela(1);
        break;
    case 2:
        projSalaExtra = 0;
        updateTela(2);
        break;
    case 3:
        tvSalaExtra = 0;
        updateTela(3);
        break;
    }
}

void deserializeModuloAnalise(const String &mensagem)
{
 JsonDocument doc; 
 DeserializationError erro = deserializeJson(doc, mensagem);
 
 if(erro)
 {
    debugError("Json inválido, corrigir formatação");
    return;
 }

 if(doc["analise"].is<JsonVariant>())
 {
  if(!doc["analise"]["timestamp"].as<u_long>() || !doc["analise"]["temperatura"].as<float>() || !doc["analise"]["umidade"].as<float>() || doc["analise"]["ruido"].as<float>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["alertaSom"].as<int>() || doc["analise"]["eco"].as<bool>())
    {
     debugError("Json invalido");
     return;
    }
  
 }
 else
 {
  timeStampAnalise = doc["analise"]["timestamp"].as<u_long>();
  temperatura = doc["analise"]["temperatura"].as<float>();
  umidade = doc["analise"]["umidade"].as<float>();
  ruido = doc["analise"]["ruido"].as<float>();
  comandoAr = doc["analise"]["comandoAr"].as<int>();
  alerta = doc["analise"]["alertaSom"].as<int>();
  eco = doc["analise"]["eco"].as<bool>();

    debugInfo("Analise desserializada com sucesso:");
    debugInfo("Timestamp: " + String(timeStampAnalise));

    sprintf(buffer, "%.1f", temperatura);
    textTempAnalise.setText(buffer);

    sprintf(buffer, "%.1f", umidade);
    textUmidAnalise.setText(buffer);

    sprintf(buffer, "%.1f", ruido);
    textRuidoAnalise.setText(buffer);

    sprintf(buffer, "%s", alerta ? "Alerta!" : "Normal");
    textAlertaRuido.setText(buffer);
 }
}

