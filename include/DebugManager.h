#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

#include <Arduino.h>
#define DEBUG_NONE 0
#define DEBUG_ERROR 1
#define DEBUG_ALL 2

void configDebug();

void debugError(const String& mensagem);
void debugInfo(const String& mensagem);

void debugNoLineError(const String& mensagem);
void debugNoLineInfo(const String& mensagem);

int getDebugLevel();

#endif