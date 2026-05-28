#include <Arduino.h>
#include "DebugManager.h"
#include "secrets.h"

int debugLevel = 2;

void debugError(const String& mensagem)
{
    if(debugLevel >= DEBUG_ERROR)
    {
        Serial.print("[ERROR] ");
        Serial.println(mensagem);
    }
}

void debugNoLineError(const String& mensagem)
{
    if(debugLevel >= DEBUG_ERROR)
    {
        Serial.println(mensagem);
    }
}

void debugInfo(const String& mensagem)
{
    if(debugLevel >= DEBUG_ALL)
    {
        Serial.print("[INFO] ");
        Serial.println(mensagem);
    }
}

void debugNoLineInfo(const String& mensagem)
{
    if(debugLevel >= DEBUG_ALL)
    {
        Serial.println(mensagem);
    }
}

void configDebug()
{
    Serial.begin(9600);
    delay(500);

    pinMode(PINO_HABILITA_DEBUG_COMPLETO, INPUT_PULLUP);

    if(digitalRead(PINO_HABILITA_DEBUG_COMPLETO) == LOW)
    {
        debugLevel = DEBUG_ALL;
    }
    else
    {
        debugLevel = DEFAULT_DEBUG_LEVEL;
    }

    for (int i = 0; i < 5; i++)
    {
        debugNoLineInfo("");
    }

    debugInfo("=====================================");
    debugInfo(" ESP32 Iniciado");
    debugInfo(" Sistema de debug ativo");
    if(debugLevel == DEBUG_ERROR)
    debugInfo(" Debug iniciado no modo apenas erro");
    else
    debugInfo(" Debug iniciado no modo completo");
    debugInfo("=====================================");

}
