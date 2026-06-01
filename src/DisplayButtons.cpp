#include <Arduino.h>
#include <Nextion.h>
#include <DisplayButtons.h>

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