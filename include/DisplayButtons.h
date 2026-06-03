#ifndef DISPLAYBUTTONS_H
#define DISPLAYBUTTONS_H
#include <Nextion.h>
#include <Arduino.h>
#include <ezTime.h>

extern Timezone tempo;

extern NexButton botaoBackLuz1;
extern NexButton botaoBackLuz2;
extern NexButton botaoBackAc1;
extern NexButton botaoBackAc2;
extern NexButton botaoBackAc3;
extern NexButton botaoBackProj1;
extern NexButton botaoBackProj2;
extern NexButton botaoBackTv1;
extern NexButton botaoBackTv2;
extern NexButton botaoBackTv3;

extern NexButton botaoLuz;
extern NexButton botaoAr;
extern NexButton botaoProj;
extern NexButton botaoTv;
extern NexButton botaoSens;
extern NexButton botaoSettings;

extern NexButton botaoLuzA;
extern NexButton botaoLuzB;
extern NexButton acenderTodasLuzes1;
extern NexButton apagarTodasLuzes1;
extern NexButton configurarTimerLuzes;
extern NexButton adicionarSalaExtraLuz;

extern NexButton botaoLuzA2;
extern NexButton botaoLuzB2;
extern NexButton botaoLuzC2;
extern NexButton botaoLuzD2;
extern NexButton acenderTodasLuzes2;
extern NexButton apagarTodasLuzes2;
extern NexButton configurarTimerLuzes2;
extern NexButton removerSalaExtraLuz;

// Tela Ar Condicionado (3, 4, 5)

extern NexButton botaoAcA;
extern  NexButton aumentarTempAc;
extern NexButton diminuirTempAc;
extern NexButton modoCoolAc;
extern NexButton modoFanAc;
extern NexButton modoDryAc;
extern NexButton modoHeatAc;
extern NexButton ventoAutoAc;
extern NexButton ventoBaixoAc;
extern NexButton ventoMedioAc;
extern NexButton ventoAltoAc;
extern NexButton botaoAcB;
extern NexButton aumentarTempAcB;
extern NexButton diminuirTempAcB;
extern NexButton modoCoolAcB;
extern NexButton modoFanAcB;
extern NexButton modoDryAcB;
extern NexButton modoHeatAcB;
extern NexButton ventoAutoAcB;
extern NexButton ventoBaixoAcB;
extern NexButton ventoMedioAcB;
extern NexButton ventoAltoAcB;
extern NexButton adicionarSalaExtraAc;

extern NexButton botaoAcA2;
extern NexButton aumentarTempAc2;
extern NexButton diminuirTempAc2;
extern NexButton modoCoolAc2;
extern NexButton modoFanAc2;
extern NexButton modoDryAc2;
extern NexButton modoHeatAc2;
extern NexButton ventoAutoAc2;
extern NexButton ventoBaixoAc2;
extern NexButton ventoMedioAc2;
extern NexButton ventoAltoAc2;
extern NexButton botaoAcB2;
extern NexButton aumentarTempAcB2;
extern NexButton diminuirTempAcB2;
extern NexButton modoCoolAcB2;
extern NexButton modoFanAcB2;
extern NexButton modoDryAcB2;
extern NexButton modoHeatAcB2;
extern NexButton ventoAutoAcB2;
extern NexButton ventoBaixoAcB2;
extern NexButton ventoMedioAcB2;
extern NexButton ventoAltoAcB2;
extern NexButton removerSalaExtraAc;
extern NexButton pageAc2;

extern NexButton botaoAcC3;
extern NexButton aumentarTempAc3;
extern NexButton diminuirTempAc3;
extern NexButton modoCoolAc3;
extern NexButton modoFanAc3;
extern NexButton modoDryAc3;
extern NexButton modoHeatAc3;
extern NexButton ventoAutoAc3;
extern NexButton ventoBaixoAc3;
extern NexButton ventoMedioAc3;
extern NexButton ventoAltoAc3;
extern NexButton removerSalaExtraAc3;
extern NexButton botaoAcD3;
extern NexButton aumentarTempAcD3;
extern NexButton diminuirTempAcD3;
extern NexButton modoCoolAcD3;
extern NexButton modoFanAcD3;
extern NexButton modoDryAcD3;
extern NexButton modoHeatAcD3;
extern NexButton ventoAutoAcD3;
extern NexButton ventoBaixoAcD3;
extern NexButton ventoMedioAcD3;
extern NexButton ventoAltoAcD3;
extern NexButton pageAc3;

// Tela Projetor (6, 7)

extern NexButton adicionarSalaExtraProj;
extern NexButton telaRetratilUp;
extern NexButton telaRetratilStop;
extern NexButton telaRetratilDown;
extern NexButton projetorAOn;
extern NexButton projetorAFreeze;

extern NexButton removerSalaExtraProj;
extern NexButton telaRetratilUp2;
extern NexButton telaRetratilStop2;
extern NexButton telaRetratilDown2;
extern NexButton projetorAOn2;
extern NexButton projetorAFreeze2;
extern NexButton telaRetratilBUp2;
extern NexButton telaRetratilBStop2;
extern NexButton telaRetratilBDown2;
extern NexButton projetorBOn2;
extern NexButton projetorBFreeze2;

// Tela TV (8, 9, 10)

extern NexButton adicionarSalaExtraTv;
extern NexButton tvAOn;
extern NexButton tvAReturn;
extern NexButton tvAVolumeUp;
extern NexButton tvAVolumeDown;
extern NexButton tvAUp;
extern NexButton tvADown;
extern NexButton tvALeft;
extern NexButton tvARight;
extern NexButton tvASelect;

extern NexButton removerSalaExtraTv;
extern NexButton tvAOn2;
extern NexButton tvAReturn2;
extern NexButton tvAVolumeUp2;
extern NexButton tvAVolumeDown2;
extern NexButton tvAUp2;
extern NexButton tvADown2;
extern NexButton tvALeft2;
extern NexButton tvARight2;
extern NexButton tvASelect2;
extern NexButton tvPageB2;

extern NexButton removerSalaExtraTv2;
extern NexButton tvBOn3;
extern NexButton tvBReturn3;
extern NexButton tvBVolumeUp3;
extern NexButton tvBVolumeDown3;
extern NexButton tvBUp3;
extern NexButton tvBDown3;
extern NexButton tvBLeft3;
extern NexButton tvBRight3;
extern NexButton tvBSelect3;
extern NexButton tvPageA3;

extern NexText textTempAnalise;
extern NexText textUmidAnalise;
extern NexText textRuidoAnalise;
extern NexText textAlertaRuido;


#endif