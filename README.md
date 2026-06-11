<div align="center">

# 🏫 Display Touch
### Sistema de automação inteligente para salas de aula

<br>

![ESP32](https://img.shields.io/badge/ESP32-S3-red?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-Framework-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![MQTT](https://img.shields.io/badge/MQTT-Protocol-660066?style=for-the-badge&logo=mqtt&logoColor=white)
![C++](https://img.shields.io/badge/C++-Language-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

<br>

> Controle completo de iluminação, ar-condicionado, projetores e TV — tudo em uma interface touchscreen intuitiva, com monitoramento ambiental em tempo real e automação inteligente por horário.

<br>

</div>

---

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Arquitetura do Sistema](#-arquitetura-do-sistema)
- [Hardware Utilizado](#-hardware-utilizado)
- [Estrutura do Software](#-estrutura-do-software)
- [Protocolo de Comunicação](#-protocolo-de-comunicação)
- [Telas da Interface](#-telas-da-interface)
- [Como Executar](#-como-executar)
- [Configuração](#-configuração)
- [Equipe](#-equipe)

---

## 🎯 Sobre o Projeto

Este é um sistema de automação embarcada desenvolvido como projeto integrador no SENAI. O objetivo é modernizar o controle dos equipamentos das salas de aula — substituindo interruptores físicos dispersos por uma única interface touchscreen centralizada.

O sistema monitora continuamente o ambiente (temperatura, umidade e ruído) e permite que professores controlem todos os dispositivos da sala sem sair do lugar, com feedback visual em tempo real e confirmação de execução de cada comando.

---

## ✨ Funcionalidades

### 💡 Iluminação
- Controle individual de cada luminária por interruptor
- Ligar/apagar todas as luzes com um toque
- Suporte a duas salas simultâneas (sala extra configurável)

### ❄️ Ar-condicionado
- Controle de até 4 unidades distribuídas em dois ESPs
- Seleção individual ou broadcast para todos os ACs de uma vez
- Ajuste de temperatura (16°C a 30°C)
- Modos: Cool, Fan, Dry, Heat
- Velocidade do ventilador: Auto, Quiet, Baixo, Médio, Alto
- **Modo Eco** — detecta automaticamente quando a sala não precisa do AC ligado

### 📽️ Projetores
- Liga/desliga e freeze por projetor
- Controle da tela retrátil (subir, pausar, descer)
- Proteção de freeze: só ativa quando o projetor estiver ligado
- Suporte a dois projetores com tópicos MQTT independentes

### 📺 TV
- Controle remoto completo via touchscreen
- Liga/desliga, volume, D-Pad e seleção

### 📊 Monitoramento Ambiental
- Temperatura e umidade em tempo real — Lado A e Lado B da sala
- Nível de ruído com alerta visual quando excede o limite
- Dados atualizados continuamente via MQTT

---

## 🏗️ Arquitetura do Sistema

```
┌─────────────────────────────────────────────────────────────┐
│                        BROKER MQTT                          │
│                   senai134/shared/projeto/                  │
└──────┬──────────────────────┬──────────────────────┬────────┘
       │                      │                      │
       ▼                      ▼                      ▼
┌─────────────┐      ┌──────────────┐      ┌──────────────────┐
│  ESP Display │      │   ESP AC     │      │  ESP Sensores    │
│  (Central)   │      │  Sala 09/10  │      │  Sala 09/10      │
│             │      │              │      │                  │
│ Nextion HMI │      │ 2x AC cada   │      │ Temp + Umidade   │
│ 10 telas    │      │ IR Blaster   │      │ Microfone ruído  │
└─────────────┘      └──────────────┘      └──────────────────┘
       │
       ├── publica → TV, AC, Lampada, Projetor, TelaRetratil
       └── recebe  → analise09, analise10, status
```

### Fluxo de um comando com QoS

```
Display                  Broker                  Dispositivo
  │                        │                          │
  │── publish(cmd+ts) ────►│                          │
  │                        │── deliver ──────────────►│
  │                        │                          │ executa
  │                        │◄── confirmacao(ts) ───────│
  │◄── deliver ────────────│                          │
  │                        │                          │
  ✓ confirmado             │                          │

  
```

---

## 🔧 Hardware Utilizado

| Componente | Descrição |
|---|---|
| **ESP32-S3** | Microcontrolador principal (display) |
| **Nextion HMI** | Display touchscreen — interface do usuário |
| **ESP32** | Controladores dos dispositivos (AC, luzes, projetores) |
| **Sensor DHT** | Temperatura e umidade ambiente |
| **Microfone** | Monitoramento de nível de ruído |
| **IR Blaster** | Envio de comandos infravermelhos para AC e TV |
| **Relés** | Controle das luminárias |

---

## 📁 Estrutura do Software

```
src/
├── main.cpp                  # Setup, loop e roteamento de mensagens MQTT
│
├── NextionManager.cpp/.h     # Interface com o display Nextion
│   ├── configurarEventosNextion()   # Registro de todos os callbacks de botão
│   ├── updateTela()                 # Navegação entre páginas
│   ├── updateBotoesAc()             # Sincronização visual dos botões do AC
│   ├── deserializeModuloAnalise()   # Processa dados do sensor sala A
│   └── deserializeModuloAnaliseB()  # Processa dados do sensor sala B
│
├── DisplayButtons.cpp/.h     # Declaração de todos os componentes Nextion
│
├── Serialize.cpp/.h          # Serialização JSON e publicação MQTT
│   ├── serializeAc()         # Comando para ar-condicionado
│   ├── serializeLampada()    # Comando para luminária individual
│   ├── onOffTodasLuzes()     # Comando para todas as luminárias
│   ├── serializeProjetor()   # Comando para projetor
│   ├── serializeTelaRetratil() # Comando para tela retrátil
└──   └── serializeTv()         # Comando para televisão

```

---

## 📡 Protocolo de Comunicação

### Tópicos de publicação

| Tópico | Payload |
|---|---|
| `.../TV` | `{"televisao":{"comando":2,"timestamp":123}}` |
| `.../AC` | `{"ar-condicionado":{"esp":1,"id_ar":1,"estado":true,"temperatura":24,"modo":0,"vento":4,"timestamp":123}}` |
| `.../lampada` | `{"lampadaSala09":{"interruptor1":1},"timestamp":123}` |
| `.../projetor09` | `{"projetor":{"estadoPower":1,"estadoCongelamento":0}}` |
| `.../telaRetratil` | `{"telaRetratil":{"tela":0,"UP":true,"PAUSE":false,"DOWN":false,"timestamp":123}}` |

### Tópicos de recebimento

| Tópico | Descrição |
|---|---|
| `.../analise09` | Dados de temperatura, umidade e ruído da sala 09 |
| `.../analise10` | Dados de temperatura, umidade e ruído da sala 10 |
| `.../status` | Confirmações de execução de comandos (QoS) |

### Payload de análise ambiental

```json
{
  "analise": {
    "timestamp": 1718000000,
    "temperatura": 23.5,
    "umidade": 60.2,
    "ruido": 45.1,
    "comandoAr": 0,
    "alertaSom": 0,
    "eco": false
  }
}
```
```

```
---

## 📱 Telas da Interface

| # | Página | Descrição |
|---|---|---|
| 0 | `inicial` | Menu principal com acesso a todos os módulos |
| 1 | `luz0` | Controle de iluminação — sala simples |
| 2 | `luz1` | Controle de iluminação — duas salas |
| 3 | `ac0` | Ar-condicionado — sala simples |
| 4 | `ac1` | Ar-condicionado — duas salas |
| 5 | `projetor0` | Projetor e tela retrátil — sala simples |
| 6 | `projetor1` | Projetor e tela retrátil — duas salas |
| 7 | `tv` | Controle remoto da televisão |
| 8 | `sensores` | Dashboard ambiental em tempo real |
| 9 | `settings` | Configurações, timers e modo light/dark |

---

## 🚀 Como Executar

### Pré-requisitos

- [PlatformIO](https://platformio.org/) ou Arduino IDE 2.x
- ESP32 Arduino Core
- Display Nextion com firmware `.tft` gravado

### Bibliotecas necessárias

```ini
; platformio.ini
monitor_speed = 115200
lib_deps =
    knolleary/PubSubClient@^2.8
    bblanchon/ArduinoJson@^7.4.3
    adafruit/Adafruit NeoPixel@^1.15.4
    https://github.com/professorThiago/ESP32_Nextion.git
    ropg/ezTime@^0.8.3
    https://github.com/kelvinmazeika/ConectividadeESP32.git
```

### Configuração de credenciais

Crie o arquivo `src/secrets.h` baseado no modelo abaixo:

```cpp
// WiFi
const char* WIFI_SSID     = "sua_rede";
const char* WIFI_PASSWORD = "sua_senha";

// MQTT
const char* MQTT_BROKER    = "seu_broker";
const int   MQTT_PORTA     = 1883;
const char* MQTT_CLIENT_ID = "esp32-display";
const char* MQTT_USER      = "";
const char* MQTT_PASSWORD  = "";

// Modo de conexão
const bool USE_AWS_IOT  = false;
const bool MQTT_USE_TLS = false;

// Tópicos
const char* TOPICOS_PUBLICAR[] = {
    "senai134/shared/projeto/TV",
    "senai134/shared/projeto/AC",
    "senai134/shared/projeto/telaRetratil",
    "senai134/shared/projeto/projetor09",
    "senai134/shared/projeto/projetor10",
    "senai134/shared/projeto/lampada"
};
const int TOTAL_TOPICOS_PUBLICAR = 6;

const char* TOPICOS_RECEBER[] = {
    "senai134/shared/projeto/analise09",
    "senai134/shared/projeto/analise10",
    "senai134/shared/projeto/status"
};
const int TOTAL_TOPICOS_RECEBER = 3;
```

### Gravando o display Nextion

1. Copie o arquivo `.tft` para um cartão microSD formatado em FAT32
2. Insira no slot do Nextion com ele desligado
3. Ligue o display — a gravação é automática
4. Remova o cartão após a conclusão

### Compilando e gravando o ESP32

```bash
# PlatformIO
pio run --target upload

# Monitor serial
pio device monitor --baud 115200
```

---

## ⚙️ Configuração

### Pinagem padrão

| Pino | Função |
|---|---|
| GPIO 17 | TX → RX do Nextion |
| GPIO 18 | RX ← TX do Nextion |

### Parâmetros ajustáveis

| Parâmetro | Localização | Padrão |
|---|---|---|
| Baud rate Nextion | `NextionManager.cpp` | 9600 |
| Intervalo NTP | `Serialize.cpp` | 3600s |
| Brilho inicial | `NextionManager.cpp` | 100% |

---

## 👨‍💻 Equipe

Desenvolvido por alunos do curso técnico de **Desenvolvimento de Sistemas** — SENAI 134, São Paulo.

<br>

---

<div align="center">

São Paulo · 2026

</div>
