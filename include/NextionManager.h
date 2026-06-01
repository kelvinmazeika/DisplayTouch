#ifndef NEXTIONMANAGER_H
#define NEXTIONMANAGER_H

#include <Arduino.h>
#include <Nextion.h>

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

void telaAcPage2();
void telaAcPage3();

void telaTvPage2();
void telaTvPage3();


#endif