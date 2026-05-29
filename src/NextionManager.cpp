#include <Arduino.h>
#include <Nextion.h>
#include "NextionManager.h"
#include "DisplayButtons.h"

// =========================================================
// CONFIGURAÇÃO DA COMUNICAÇÃO COM O NEXTION
// =========================================================

bool luzSalaExtra = 0;
bool arSalaExtra = 0;
bool projSalaExtra = 0;
bool tvSalaExtra = 0;

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

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();

void botaoBack();
void telaLuz();
void telaAr();
void telaProj();
void telaTv();
void telaSens();
void telaSettings();

void addSalaExtraLuz();
void addSalaExtraAc();
void addSalaExtraProj();
void addSalaExtraTv();
void removeSalaExtraLuz();
void removeSalaExtraAc();
void removeSalaExtraProj();
void removeSalaExtraTv();


void configurarNextion()
{
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
    // Garante que o display esteja na página principal.
    // O nome "page0" precisa ser igual ao nome da página no Nextion Editor.
    sendCommand("page inicial");

    delay(500);
}

void configurarEventosNextion()
{
    botaoBackLuz1.attachPop(botaoBack);
    botaoBackLuz2.attachPop(botaoBack);
    botaoBackAc1.attachPop(botaoBack);
    botaoBackAc2.attachPop(botaoBack);
    botaoBackAc3.attachPop(botaoBack);
    botaoBackProj1.attachPop(botaoBack);
    botaoBackProj2.attachPop(botaoBack);
    botaoBackTv1.attachPop(botaoBack);
    botaoBackTv2.attachPop(botaoBack);
    botaoBackTv3.attachPop(botaoBack);
    
    botaoLuz.attachPop(telaLuz);
    botaoAr.attachPop(telaAr);
    botaoProj.attachPop(telaProj);
    botaoTv.attachPop(telaTv);
    botaoSens.attachPop(telaSens);
    botaoSettings.attachPop(telaSettings);

    adicionarSalaExtraAc.attachPop(addSalaExtraAc);
    adicionarSalaExtraLuz.attachPop(addSalaExtraLuz);
    adicionarSalaExtraProj.attachPop(addSalaExtraProj);
    adicionarSalaExtraTv.attachPop(addSalaExtraTv);

    removerSalaExtraLuz.attachPop(removeSalaExtraLuz);
    removerSalaExtraAc.attachPop(removeSalaExtraAc);
    removerSalaExtraAc3.attachPop(removeSalaExtraAc);
    removerSalaExtraProj.attachPop(removeSalaExtraProj);
    removerSalaExtraTv.attachPop(removeSalaExtraTv);
    removerSalaExtraTv2.attachPop(removeSalaExtraTv);


    // Limpa a lista interna de componentes monitorados.
    nexClearListenList();

    // Registra quais componentes devem ser ouvidos pelo ESP32.
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
}

void botaoBack()
{
    sendCommand("page inicial");
}

void telaLuz()
{
    if(luzSalaExtra)
    sendCommand("page luz2");
    else
    sendCommand("page luz1");
}

void telaAr()
{
    if(arSalaExtra)
    sendCommand("page ac2");
    else
    sendCommand("page ac1");
}

void telaProj()
{
    if(projSalaExtra)
    sendCommand("page proj2");
    else
    sendCommand("page proj1");
}

void telaTv()
{
    if(tvSalaExtra)
    sendCommand("page tv2");
    else
    sendCommand("page tv1");
}

void telaSens()
{
    sendCommand("page sens");
}

void telaSettings()
{
    sendCommand("page settings");
}

void addSalaExtraLuz()
{
    luzSalaExtra = 1;
    telaLuz();
}

void addSalaExtraAc()
{
    arSalaExtra = 1;
    telaAr();
}

void addSalaExtraProj()
{
    projSalaExtra = 1;
    telaProj();
}

void addSalaExtraTv()
{
    tvSalaExtra = 1;
    telaTv();
}

void removeSalaExtraLuz()
{
    luzSalaExtra = 0;
    telaLuz();
}

void removeSalaExtraAc()
{
    arSalaExtra = 0;
    telaAr();
}

void removeSalaExtraProj()
{
    projSalaExtra = 0;
    telaProj();
}

void removeSalaExtraTv()
{
    tvSalaExtra = 0;
    telaTv();
}

