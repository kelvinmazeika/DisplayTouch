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

void onOffLuz(int sala, bool frenteAtras, bool estadoLampada);
void onOffTv(int sala, bool estado);

void deserializeModuloAnalise(const String &mensagem);


#endif