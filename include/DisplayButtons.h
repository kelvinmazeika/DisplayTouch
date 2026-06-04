#ifndef DISPLAYBUTTONS_H
#define DISPLAYBUTTONS_H
#include <Nextion.h>
#include <Arduino.h>
#include <ezTime.h>

extern bool luzSalaExtra = 0;
extern bool arSalaExtra = 0;
extern bool projSalaExtra = 0;

extern uint32_t acSelecionados[4];

uint32_t projetoresSelecionados[2];

extern Timezone tempo;

//tela inicial
extern NexButton telaLuz;
extern NexButton telaAc;
extern NexButton telaProj;
extern NexButton telaTv;
extern NexButton telaSensor;
extern NexButton telaSettings;

//tela luz 1, 2
extern NexButton backLuz1;
extern NexButton adicionarSalaExtraLuz;

extern NexDSButton botaoLuzA1;
extern NexDSButton botaoLuzB1;
extern NexButton acenderTodasLuzes1;
extern NexButton apagarTodasLuzes1;
extern NexButton configurarTimerLuzes1;

extern NexButton backLuz2;
extern NexButton removerSalaExtraLuz;

extern NexDSButton botaoLuzA2;
extern NexDSButton botaoLuzB2;
extern NexDSButton botaoLuzC2;
extern NexDSButton botaoLuzD2;
extern NexButton acenderTodasLuzes2;
extern NexButton apagarTodasLuzes2;
extern NexButton configurarTimerLuzes2;

//tela ar condicionado 3, 4
extern NexButton backAc1;
extern NexButton adicionarSalaExtraAc;
extern NexText textoTemp1;

extern NexDSButton botaoAcOnOff;
extern NexDSButton selecionarAcA1;
extern NexDSButton selecionarAcB1;
extern NexButton aumentarTempAc1;
extern NexButton diminuirTempAc1;
extern NexDSButton modoCoolAc1;
extern NexDSButton modoFanAc1;
extern NexDSButton modoDryAc1;
extern NexDSButton modoHeatAc1;
extern NexDSButton ventoAutoAc1;
extern NexDSButton ventoBaixoAc1;
extern NexDSButton ventoMedioAc1;
extern NexDSButton ventoAltoAc1;
extern NexDSButton ventoSilentAc1;
extern NexButton confirmarConfigAc1;

extern NexButton backAc2;
extern NexButton removerSalaExtraAc;
extern NexText textoTemp2;

extern NexDSButton botaoAcOnOff2;
extern NexDSButton selecionarAcA2;
extern NexDSButton selecionarAcB2;
extern NexDSButton selecionarAcC2;
extern NexDSButton selecionarAcD2;
extern NexButton aumentarTempAc2;
extern NexButton diminuirTempAc2;
extern NexDSButton modoCoolAc2;
extern NexDSButton modoFanAc2;
extern NexDSButton modoDryAc2;
extern NexDSButton modoHeatAc2;
extern NexDSButton ventoAutoAc2;
extern NexDSButton ventoBaixoAc2;
extern NexDSButton ventoMedioAc2;
extern NexDSButton ventoAltoAc2;
extern NexDSButton ventoSilentAc2;
extern NexButton confirmarConfigAc2;

//tela projetor 5, 6
extern NexButton backProj1;
extern NexButton adicionarSalaExtraProj;

extern NexButton telaRetratilUp1;
extern NexButton telaRetratilStop1;
extern NexButton telaRetratilDown1;
extern NexDSButton projetorOnOff1;
extern NexDSButton projetorFreeze1;

extern NexButton backProj2;
extern NexButton removerSalaExtraProj;

extern NexButton telaRetratilUp2;
extern NexButton telaRetratilStop2;
extern NexButton telaRetratilDown2;
extern NexDSButton projetorOnOff2;
extern NexDSButton projetorFreeze2;
extern NexDSButton selecionarProjetorA;
extern NexDSButton selecionarProjetorB;

//tela tv 7
extern NexButton backTv;

extern NexButton returnTv;
extern NexButton aumentarVolumeTv;
extern NexButton diminuirVolumeTv;
extern NexButton dPadUpTv;
extern NexButton dPadDownTv;
extern NexButton dPadLeftTv;
extern NexButton dPadRightTv;
extern NexButton dPadSelectTv;
extern NexDSButton botaoTvOnOff;

//tela sensor 8
extern NexButton backSensor;
extern NexText textoTempLadoA;
extern NexText textoUmidadeLadoA;
extern NexText textoRuidoLadoA;
extern NexText textoTempLadoB;
extern NexText textoUmidadeLadoB;
extern NexText textoRuidoLadoB;
extern NexText textoAmbienteSensor;

//tela settings 9
extern NexButton backSettings;


#endif