//! WiFIManager.cpp

#ifndef WIFIMANAGER_CPP
#define WIFIMANAGER_CPP
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "WiFiManager.h"
#include "secrets.h"
#include "DebugManager.h"

bool wifiIsConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void connectToWifi()
{
    debugInfo("=============================");
    debugInfo("Iniciando conexão ao WiFi...");
    debugInfo("=============================");

    WiFi.mode(WIFI_STA); // Configura o ESP32 como Station (conecta a um roteador existente)

    WiFi.begin(ssid, password); // Inicia a conexão com SSID e Senha

    debugInfo("Conectando ao WiFi...");

    int attemptsToConnect = 0;
    const int maxAttemptsToConnect = 30;

    // Aguarda a conexão com no máximo 30 tentativas
    while (WiFi.status() != WL_CONNECTED && attemptsToConnect <= maxAttemptsToConnect)
    {
        delay(500);
        debugNoLineInfo(".");
        attemptsToConnect++;
    }

    debugInfo("");

    if (WiFi.status() == WL_CONNECTED)
    {
        debugInfo("Conectado ao Wifi.");
        debugInfo("Endereço IP: ");
        debugInfo(String(WiFi.localIP()));
    }
    else
    {
        debugError("Falha ao conectar ao WiFi.");
        debugError("Verifique o SSID, Senha e o Sinal da rede.");
    }
}

void grantWiFiAccess()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        debugInfo("WiFi Desconectado. Tentando reconexão!");
        connectToWifi();
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        debugError("Não foi possível reconectar ao WiFi.");
    }
}
#endif