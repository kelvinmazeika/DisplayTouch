#include <Arduino.h>
#include <Nextion.h>
#include "DisplayButtons.h"
#include "NextionManager.h"
#include "Serialize.h"

// =========================================================
// CONFIGURAÇÃO DA COMUNICAÇÃO COM O NEXTION
// =========================================================

bool luzSalaExtra = 0;
bool arSalaExtra = 0;
bool projSalaExtra = 0;
bool tvSalaExtra = 0;
uint8_t acaoTv;

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

    // Tela Sala Extra AC
    pageAc2.attachPop(telaAcPage2);
    pageAc3.attachPop(telaAcPage3);
    
    // Tela Sala Extra TV
    tvPageB2.attachPop(telaTvPage2);
    tvPageA3.attachPop(telaTvPage3);



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
}

void botaoBack()
{
    Serial.println("Botao back pressionado");
    sendCommand("page inicial");
}

void telaLuz()
{
    Serial.println("Botao luz pressionado");
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
<<<<<<< HEAD
=======

void telaAcPage2()
{
    sendCommand("page ac3");
}

void telaAcPage3()
{
    sendCommand("page ac2");
}

void telaTvPage2()
{
    sendCommand("page tv3");
}

void telaTvPage3()
{
    sendCommand("page tv2");
}

void 
>>>>>>> 1859c850e311a0a8d99744e0c6f06a27003379a9
