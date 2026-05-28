#include <Arduino.h>
#include <Nextion.h>

// =========================================================
// CONFIGURAÇÃO DA COMUNICAÇÃO COM O NEXTION
// =========================================================

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

// Evite chamar a variável de j0, porque existe uma função matemática j0()
// na biblioteca padrão do C/C++.
NexProgressBar barraJ0(0, 2, "j0");

// Componentes que recebem toque
NexButton botaoB0(0, 3, "b0");
NexSlider sliderH0(0, 4, "h0");
NexDSButton botaoDualBt0(0, 5, "bt0");

// Textos usados para mostrar o estado dos componentes
NexText textoT1(0, 6, "t1");
NexText textoT2(0, 7, "t2");
NexText textoT3(0, 8, "t3");
NexText textoT4(0, 9, "t4");

// =========================================================
// VARIÁVEIS DE CONTROLE DA APLICAÇÃO
// =========================================================

uint32_t valorBarra = 0;
uint32_t contadorBotao = 0;
uint32_t valorSlider = 0;
uint32_t estadoBotaoDual = 0;

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
    sendCommand("page page0");

    delay(500);

    // Define os valores iniciais da aplicação.
    valorBarra = 0;
    contadorBotao = 0;
    valorSlider = 0;
    estadoBotaoDual = 0;

    // Atualiza os componentes visuais do display.
    barraJ0.setValue(valorBarra);
    sliderH0.setValue(valorSlider);
    botaoDualBt0.setValue(estadoBotaoDual);

    // Atualiza os textos iniciais.
    textoT1.setText("j0 = 0%");
    textoT2.setText("b0 aguardando");
    textoT3.setText("h0 = 0");
    textoT4.setText("bt0 = Desligado");
}

// =========================================================
// CONFIGURAÇÃO DOS EVENTOS DO NEXTION
// =========================================================

void configurarEventosNextion()
{
    // attachPop() executa a função quando o componente é solto.
    // No Nextion Editor, use "Send Component ID" em Touch Release Event.

    botaoB0.attachPop(botaoBack);
    

    // Limpa a lista interna de componentes monitorados.
    nexClearListenList();

    // Registra quais componentes devem ser ouvidos pelo ESP32.
    nexListen(botaoB0);
    nexListen(sliderH0);
    nexListen(botaoDualBt0);
}

void botaoBack()
{
    Serial.println("Botao b0 solto.");
    sendCommand("page inicial");
}

