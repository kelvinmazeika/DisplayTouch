#ifndef NEXTIONMANAGER_H
#define NEXTIONMANAGER_H

#include <Arduino.h>
#include <Nextion.h>

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();

void updateTela(int modulo);

void addSalaExtra(int modulo);
void removeSalaExtra(int modulo);

void telaAcPage2();
void telaAcPage3();

void telaTvPage2();
void telaTvPage3();


#endif