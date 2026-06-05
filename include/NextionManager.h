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

void deserializeModuloAnalise(const String &mensagem);

void updateBotoesAc(bool confirmado);

#endif