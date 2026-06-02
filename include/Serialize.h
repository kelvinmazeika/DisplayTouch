#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <Arduino.h>
#include <MqttManager.h>

#define TOPICO_ANALISE 0
#define TOPICO_TV 1
#define TOPICO_PROJ_09 2
#define TOPICO_PROJ_10 3
#define TOPICO_AC_09 4
#define TOPICO_AC_10 5 
#define TOPICO_LAMP 6 
#define TOPICO_TELA_09 7
#define TOPICO_TELA_10 8
 

void voltarHome();

void publicarComandProjetorTela(const char *sala, bool comando);
void publicarTV(int acao);
void publicarAC(); //Verificar JSON e terminar de preencher parametros

void serializeTv(int comando);
void serializeLampada(int sala, bool estadoLampadaTras, bool estadoLampadaFrente);

#endif