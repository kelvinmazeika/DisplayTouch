#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <Arduino.h>
#include <ezTime.h>
#include "MqttManager.h"


#define TOPICO_ANALISE 0
#define TOPICO_TV 1
#define TOPICO_PROJ_09 2
#define TOPICO_PROJ_10 3
#define TOPICO_AC 4
#define TOPICO_LAMP 5 
#define TOPICO_TELA_09 6
#define TOPICO_TELA_10 7
 

void iniciaTimestamp();

void publicarComandProjetor(const char *sala, bool power, bool congelamento);
bool projEstadoPower = 0;
bool projEstadoFreeze = 0;
void serializarAc(int esp, int qualAr, bool estado, int temp, int modo, int vento); //Verificar JSON e terminar de preencher parametros

void serializeTv(int comando);
void serializeLampada(int sala, bool estadoLampadaTras, bool estadoLampadaFrente);

void onOffTodasLuzes(bool estadoLuzes);


#endif