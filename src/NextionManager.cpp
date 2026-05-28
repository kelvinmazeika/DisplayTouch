#include <Arduino.h>
#include <Nextion.h>

// =========================================================
// CONFIGURAÇÃO DA COMUNICAÇÃO COM O NEXTION
// =========================================================

bool luzSalaExtra = 0;

// Velocidade padrão de comunicação serial do Nextion
const uint32_t BAUD_NEXTION = 9600;

// RX do ESP32-S3 ligado ao TX do Nextion
const int8_t PINO_RX_NEXTION = 18;

// TX do ESP32-S3 ligado ao RX do Nextion
const int8_t PINO_TX_NEXTION = 17;

// =========================================================
// COMPONENTES DO NEXTION
// =========================================================

// A estrutura é:
// Classe nomeDoObjeto(pageId, componentId, "nomeNoNextion");

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

// =========================================================
// VARIÁVEIS DE CONTROLE DA APLICAÇÃO
// =========================================================

// Buffer usado para montar textos antes de enviar ao display
char texto[50];

// =========================================================
// PROTÓTIPOS DAS FUNÇÕES
// =========================================================

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();

void botaoBack();

// =========================================================
// CONFIGURAÇÃO DO NEXTION
// =========================================================

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

// =========================================================
// CONFIGURAÇÃO INICIAL DA TELA
// =========================================================

void configurarTelaInicial()
{
    // Garante que o display esteja na página principal.
    // O nome "page0" precisa ser igual ao nome da página no Nextion Editor.
    sendCommand("page inicial");

    delay(500);
}

// =========================================================
// CONFIGURAÇÃO DOS EVENTOS DO NEXTION
// =========================================================

void configurarEventosNextion()
{
    // attachPop() executa a função quando o componente é solto.
    // No Nextion Editor, use "Send Component ID" em Touch Release Event.

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

    nexListen(botaoLuz);
}

void botaoBack()
{
    Serial.println("Botao b0 solto.");
    sendCommand("page inicial");
}

void telaLuz()
{
    if(luzSalaExtra)
    sendCommand("page luz2");
    else
    sendCommand("page luz1");
}
