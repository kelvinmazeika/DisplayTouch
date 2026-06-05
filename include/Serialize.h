#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <Arduino.h>
#include <ezTime.h>
#include "MqttManager.h"


#define TOPICO_TV 0

 

void iniciaTimestamp();

void serializeProjetor(int power, bool congelamento);

void serializeAc(bool estado, int temp, int modo, int vento); //Verificar JSON e terminar de preencher parametros

void serializeTv(int comando);
void serializeLampada(int sala, bool lampadaFrente, int estadoLampada);
void serializeTelaRetratil(bool up, bool down, bool pause);

void onOffTodasLuzes(bool estadoLuzes);


#endif