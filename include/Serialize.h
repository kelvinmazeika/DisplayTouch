#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <Arduino.h>


#define TOPICO_ANALISE_09 0
#define TOPICO_ANALISE_10 1


#define TOPICO_TV 0
#define TOPICO_AC 1
#define TOPICO_TELA 2
#define TOPICO_PROJ 3
#define TOPICO_LAMP 4

 

void iniciaTimestamp();

void serializeProjetor(int acao);

void serializeAc(int estado, int temp, int modo, int vento); //Verificar JSON e terminar de preencher parametros

void serializeTv(int comando);
void serializeLampada(int sala, bool lampadaFrente, int estadoLampada);
void serializeTelaRetratil(int acao);

void onOffTodasLuzes(int estadoLuzes);



#endif