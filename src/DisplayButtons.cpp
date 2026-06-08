#include <Arduino.h>
#include <Nextion.h>
#include <DisplayButtons.h>

bool luzSalaExtra = 0;
bool arSalaExtra = 0;
bool projSalaExtra = 0;

uint32_t estadoProj[2] = {0, 0}; 
uint32_t estadoProjFreeze[2] = {0, 0};

uint32_t projetoresSelecionados[2] = {0, 0};

uint32_t acSelecionados[4] = {0, 0, 0, 0};

Timezone tempo;

//tela inicial
NexButton telaLuz(0, 2, "b0");
NexButton telaAc(0, 3, "b1");
NexButton telaProj(0, 4, "b2");
NexButton telaTv(0, 5, "b3");
NexButton telaSensor(0, 6, "b4");
NexButton telaSettings(0, 7, "b5");

//tela luz 1, 2
NexButton backLuz1(1, 4, "b0");
NexButton adicionarSalaExtraLuz(1, 8, "b1");

NexDSButton botaoLuzA1(1, 2, "bt0");
NexDSButton botaoLuzB1(1, 3, "bt1");
NexButton acenderTodasLuzes1(1, 5, "b2");
NexButton apagarTodasLuzes1(1, 6, "b3");
NexButton configurarTimerLuzes1(1, 7, "b4");

NexButton backLuz2(2, 2, "b0");
NexButton removerSalaExtraLuz(2, 3, "b1");

NexDSButton botaoLuzA2(2, 4, "bt0");
NexDSButton botaoLuzB2(2, 5, "bt1");
NexDSButton botaoLuzC2(2, 6, "bt2");
NexDSButton botaoLuzD2(2, 7, "bt3");
NexButton acenderTodasLuzes2(2, 8, "b2");
NexButton apagarTodasLuzes2(2, 9, "b3");
NexButton configurarTimerLuzes2(2, 10, "b4");

//tela ar condicionado 3, 4
NexButton backAc1(3, 2, "b0");
NexButton adicionarSalaExtraAc(3, 3, "b1");
NexText textoTemp1(3, 9, "t0");

NexDSButton botaoAcOnOff(3, 4, "bt0");
NexDSButton selecionarAcA1(3, 5, "bt1");
NexDSButton selecionarAcB1(3, 6, "bt2");
NexButton aumentarTempAc1(3, 7, "b2");
NexButton diminuirTempAc1(3, 8, "b3");
NexDSButton modoCoolAc1(3, 10, "bt3");
NexDSButton modoFanAc1(3, 11, "bt4");
NexDSButton modoDryAc1(3, 12, "bt5");
NexDSButton modoHeatAc1(3, 13, "bt6");
NexDSButton ventoAutoAc1(3, 14, "bt7");
NexDSButton ventoBaixoAc1(3, 15, "bt8");
NexDSButton ventoMedioAc1(3, 16, "bt9");
NexDSButton ventoAltoAc1(3, 17, "bt10");
NexDSButton ventoSilentAc1(3, 18, "bt11");
NexButton confirmarConfigAc1(3, 19, "b4");

NexButton backAc2(4, 2, "b0");
NexButton removerSalaExtraAc(4, 3, "b1");
NexText textoTemp2(4, 11, "t0");

NexDSButton botaoAcOnOff2(4, 4, "bt0");
NexDSButton selecionarAcA2(4, 5, "bt1");
NexDSButton selecionarAcB2(4, 6, "bt2");
NexDSButton selecionarAcC2(4, 7, "bt3");
NexDSButton selecionarAcD2(4, 8, "bt4");
NexButton aumentarTempAc2(4, 9, "b2");
NexButton diminuirTempAc2(4, 10, "b3");
NexDSButton modoCoolAc2(4, 12, "bt5");
NexDSButton modoFanAc2(4, 13, "bt6");
NexDSButton modoDryAc2(4, 14, "bt7");
NexDSButton modoHeatAc2(4, 15, "bt8");
NexDSButton ventoAutoAc2(4, 16, "bt9");
NexDSButton ventoBaixoAc2(4, 17, "bt10");
NexDSButton ventoMedioAc2(4, 18, "bt11");
NexDSButton ventoAltoAc2(4, 19, "bt12");
NexDSButton ventoSilentAc2(4, 20, "bt13");
NexButton confirmarConfigAc2(4, 21, "b4");

//tela projetor 5, 6
NexButton backProj1(5, 2, "b0");
NexButton adicionarSalaExtraProj(5, 3, "b1");

NexButton telaRetratilUp1(5, 4, "b2");
NexButton telaRetratilStop1(5, 5, "b3");
NexButton telaRetratilDown1(5, 6, "b4");
NexDSButton projetorOnOff1(5, 7, "bt0");
NexDSButton projetorFreeze1(5, 8, "bt1");

NexButton backProj2(6, 2, "b0");
NexButton removerSalaExtraProj(6, 3, "b1");

NexButton telaRetratilUp2(6, 4, "b2");
NexButton telaRetratilStop2(6, 5, "b3");
NexButton telaRetratilDown2(6, 6, "b4");
NexDSButton projetorOnOff2(6, 7, "bt0");
NexDSButton projetorFreeze2(6, 8, "bt1");
NexDSButton selecionarProjetorA(6, 9, "bt2");
NexDSButton selecionarProjetorB(6, 10, "bt3");

//tela tv 7
NexButton backTv(7, 2, "b0");

NexButton returnTv(7, 4, "b1");
NexButton aumentarVolumeTv(7, 5, "b2");
NexButton diminuirVolumeTv(7, 6, "b3");
NexButton dPadUpTv(7, 7, "b4");
NexButton dPadDownTv(7, 8, "b5");
NexButton dPadLeftTv(7, 9, "b6");
NexButton dPadRightTv(7, 10, "b7");
NexButton dPadSelectTv(7, 11, "b8");
NexDSButton botaoTvOnOff(7, 3, "bt0");

//tela sensor 8
NexButton backSensor(8, 2, "b0");
NexText textoTempLadoA(8, 3, "t0");
NexText textoUmidadeLadoA(8, 4, "t1");
NexText textoRuidoLadoA(8, 5, "t2");
NexText textoTempLadoB(8, 7, "t4");
NexText textoUmidadeLadoB(8, 8, "t5");
NexText textoRuidoLadoB(8, 9, "t6");
NexText textoAmbienteSensor(8, 6, "t3");

//tela settings 9
NexButton backSettings(9, 2, "b0");