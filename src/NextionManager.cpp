#include <Arduino.h>
#include <Nextion.h>
#include "DisplayButtons.h"
#include "NextionManager.h"

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



NexButton botaoBackLuz1(1, 4, "b0");
NexButton botaoBackLuz2(2, 8, "b0");
NexButton botaoBackAc1(3, 2, "b0");
NexButton botaoBackAc2(5, 2, "b0");
NexButton botaoBackAc3(5, 2, "b0");
NexButton botaoBackProj1(6, 2, "b0");
NexButton botaoBackProj2(7, 2, "b0");
NexButton botaoBackTv1(8, 2, "b0");
NexButton botaoBackTv2(9, 2, "b0");
NexButton botaoBackTv3(10, 2, "b0");

// Tela Inicial

NexButton botaoLuz(0, 2, "b0");
NexButton botaoAr(0, 3, "b1");
NexButton botaoProj(0, 4, "b2");
NexButton botaoTv(0, 5, "b3");
NexButton botaoSens(0, 6, "b4");
NexButton botaoSettings(0, 7, "b5");

// Tela Luz (1, 2, 3)

NexButton botaoLuzA(1, 2, "b1");
NexButton botaoLuzB(1, 5, "b2");
NexButton acenderTodasLuzes1(1, 3, "b3");
NexButton apagarTodasLuzes1(1, 6, "b4");
NexButton configurarTimerLuzes(1, 7, "b5");
NexButton adicionarSalaExtraLuz(1, 8, "b6");

NexButton botaoLuzA2(2, 2, "b1");
NexButton botaoLuzB2(2, 3, "b2");
NexButton botaoLuzC2(2, 9, "b7");
NexButton botaoLuzD2(2, 10, "b8");
NexButton acenderTodasLuzes2(2, 4, "b3");
NexButton apagarTodasLuzes2(2, 5, "b4");
NexButton configurarTimerLuzes2(2, 6, "b5");
NexButton removerSalaExtraLuz(2, 7, "b6");

// Tela Ar Condicionado (3, 4, 5)

NexButton botaoAcA(3, 4, "b2");
NexButton aumentarTempAc(3, 5, "b3");
NexButton diminuirTempAc(3, 6, "b4");
NexButton modoCoolAc(3, 7, "b5");
NexButton modoFanAc(3, 8, "b6");
NexButton modoDryAc(3, 9, "b7");
NexButton modoHeatAc(3, 10, "b8");
NexButton ventoAutoAc(3, 11, "b9");
NexButton ventoBaixoAc(3, 12, "b10");
NexButton ventoMedioAc(3, 13, "b11");
NexButton ventoAltoAc(3, 14, "b12");
NexButton botaoAcB(3, 15, "b13");
NexButton aumentarTempAcB(3, 16, "b14");
NexButton diminuirTempAcB(3, 17, "b15");
NexButton modoCoolAcB(3, 18, "b16");
NexButton modoFanAcB(3, 19, "b17");
NexButton modoDryAcB(3, 20, "b18");
NexButton modoHeatAcB(3, 21, "b19");
NexButton ventoAutoAcB(3, 22, "b20");
NexButton ventoBaixoAcB(3, 23, "b21");
NexButton ventoMedioAcB(3, 24, "b22");
NexButton ventoAltoAcB(3, 25, "b23");
NexButton adicionarSalaExtraAc(3, 3, "b1");

NexButton botaoAcA2(4, 4, "b2");
NexButton aumentarTempAc2(4, 5, "b3");
NexButton diminuirTempAc2(4, 6, "b4");
NexButton modoCoolAc2(4, 7, "b5");
NexButton modoFanAc2(4, 8, "b6");
NexButton modoDryAc2(4, 9, "b7");
NexButton modoHeatAc2(4, 10, "b8");
NexButton ventoAutoAc2(4, 11, "b9");
NexButton ventoBaixoAc2(4, 12, "b10");
NexButton ventoMedioAc2(4, 13, "b11");
NexButton ventoAltoAc2(4, 14, "b12");
NexButton botaoAcB2(4, 15, "b13");
NexButton aumentarTempAcB2(4, 16, "b14");
NexButton diminuirTempAcB2(4, 17, "b15");
NexButton modoCoolAcB2(4, 18, "b16");
NexButton modoFanAcB2(4, 19, "b17");
NexButton modoDryAcB2(4, 20, "b18");
NexButton modoHeatAcB2(4, 21, "b19");
NexButton ventoAutoAcB2(4, 22, "b20");
NexButton ventoBaixoAcB2(4, 23, "b21");
NexButton ventoMedioAcB2(4, 24, "b22");
NexButton ventoAltoAcB2(4, 25, "b23");
NexButton removerSalaExtraAc(4, 3, "b1");
NexButton pageAc2(4, 26, "b24");

NexButton botaoAcC3(5, 4, "b2");
NexButton aumentarTempAc3(5, 5, "b3");
NexButton diminuirTempAc3(5, 6, "b4");
NexButton modoCoolAc3(5, 7, "b5");
NexButton modoFanAc3(5, 8, "b6");
NexButton modoDryAc3(5, 9, "b7");
NexButton modoHeatAc3(5, 10, "b8");
NexButton ventoAutoAc3(5, 11, "b9");
NexButton ventoBaixoAc3(5, 12, "b10");
NexButton ventoMedioAc3(5, 13, "b11");
NexButton ventoAltoAc3(5, 14, "b12");
NexButton removerSalaExtraAc3(5, 3, "b1");
NexButton botaoAcD3(5, 15, "b13");
NexButton aumentarTempAcD3(5, 16, "b14");
NexButton diminuirTempAcD3(5, 17, "b15");
NexButton modoCoolAcD3(5, 18, "b16");
NexButton modoFanAcD3(5, 19, "b17");
NexButton modoDryAcD3(5, 20, "b18");
NexButton modoHeatAcD3(5, 21, "b19");
NexButton ventoAutoAcD3(5, 22, "b20");
NexButton ventoBaixoAcD3(5, 23, "b21");
NexButton ventoMedioAcD3(5, 24, "b22");
NexButton ventoAltoAcD3(5, 25, "b23");
NexButton pageAc3(5, 26, "b24");

// Tela Projetor (6, 7)

NexButton adicionarSalaExtraProj(6, 3, "b1");
NexButton telaRetratilUp(6, 4, "b2");
NexButton telaRetratilStop(6, 5, "b3");
NexButton telaRetratilDown(6, 6, "b4");
NexButton projetorAOn(6, 7, "b5");
NexButton projetorAFreeze(6, 8, "b6");

NexButton removerSalaExtraProj(7, 3, "b1");
NexButton telaRetratilUp2(7, 4, "b2");
NexButton telaRetratilStop2(7, 5, "b3");
NexButton telaRetratilDown2(7, 6, "b4");
NexButton projetorAOn2(7, 7, "b5");
NexButton projetorAFreeze2(7, 8, "b6");
NexButton telaRetratilBUp2(7, 9, "b7");
NexButton telaRetratilBStop2(7, 10, "b8");
NexButton telaRetratilBDown2(7, 11, "b9");
NexButton projetorBOn2(7, 12, "b10");
NexButton projetorBFreeze2(7, 13, "b11");

// Tela TV (8, 9, 10)

NexButton adicionarSalaExtraTv(8, 3, "b1");
NexButton tvAOn(8, 4, "b2");
NexButton tvAReturn(8, 5, "b3");
NexButton tvAVolumeUp(8, 6, "b4");
NexButton tvAVolumeDown(8, 7, "b5");
NexButton tvAUp(8, 8, "b6");
NexButton tvADown(8, 9, "b7");
NexButton tvALeft(8, 10, "b8");
NexButton tvARight(8, 11, "b9");
NexButton tvASelect(8, 12, "b10");

NexButton removerSalaExtraTv(9, 3, "b1");
NexButton tvAOn2(9, 4, "b2");
NexButton tvAReturn2(9, 5, "b3");
NexButton tvAVolumeUp2(9, 6, "b4");
NexButton tvAVolumeDown2(9, 7, "b5");
NexButton tvAUp2(9, 8, "b6");
NexButton tvADown2(9, 9, "b7");
NexButton tvALeft2(9, 10, "b8");
NexButton tvARight2(9, 11, "b9");
NexButton tvASelect2(9, 12, "b10");
NexButton tvPageB2(9, 13, "b11");

NexButton removerSalaExtraTv2(10, 3, "b1");
NexButton tvBOn3(10, 4, "b2");
NexButton tvBReturn3(10, 5, "b3");
NexButton tvBVolumeUp3(10, 6, "b4");
NexButton tvBVolumeDown3(10, 7, "b5");
NexButton tvBUp3(10, 8, "b6");
NexButton tvBDown3(10, 9, "b7");
NexButton tvBLeft3(10, 10, "b8");
NexButton tvBRight3(10, 11, "b9");
NexButton tvBSelect3(10, 12, "b10");
NexButton tvPageA3(10, 13, "b11");



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
    sendCommand("bkcmd=3"); // <-- adiciona isso, habilita respostas do display
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


    // Limpa a lista interna de componentes monitorados.

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

