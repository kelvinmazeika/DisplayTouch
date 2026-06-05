#include <Arduino.h>
#include <Nextion.h>
#include "DisplayButtons.h"
#include "NextionManager.h"
#include "Serialize.h"
#include <ArduinoJson.h>
#include <DebugManager.h>

// =========================================================
// Variaveis de estado dos módulos e da tela
// =========================================================

uint8_t acaoTv;

uint32_t estadoLuzes[2][2] = {{0, 0}, {0, 0}};
int tela = 0;

float temperatura;
float umidade;
float ruido;
int comandoAr;
int alerta;
bool eco;
u_long timeStampAnalise;
char buffer[100];

uint32_t estadoAc = 0;
int temperaturaAc = 24;
uint32_t modoAc = 0;
uint32_t ventoAc = 0;

uint32_t estadoProjetor = 0;
uint32_t estadoFreezeProjetor = 0;


const uint32_t BAUD_NEXTION = 9600;
const int8_t PINO_RX_NEXTION = 18;
const int8_t PINO_TX_NEXTION = 17;
char texto[50];

// =========================================================
// PROTÓTIPOS DAS FUNÇÕES
// =========================================================

void configurarNextion()
{
    Serial.println("Chamando nextion agora");
    bool nextionOk = nexInit(BAUD_NEXTION, PINO_RX_NEXTION, PINO_TX_NEXTION);
    if (!nextionOk)
    {
        Serial.println("Aviso: o Nextion nao confirmou a inicializacao.");
    }
    else
    {
        Serial.println("Nextion inicializado.");
    }
}

void configurarTelaInicial()
{
    sendCommand("page inicial");
    delay(500);
    sendCommand("bkcmd=3");
    delay(100);
}

void configurarEventosNextion()
{
    // tela inicial 0
    telaLuz.attachPush([]()
                       { updateTela(1); });
    telaAc.attachPush([]()
                      { updateTela(2); });
    telaProj.attachPush([]()
                        { updateTela(3); });
    telaTv.attachPush([]()
                      { updateTela(4); });
    telaSensor.attachPush([]()
                          { updateTela(5); });
    telaSettings.attachPush([]()
                            { updateTela(6); });

    // tela luz 1, 2
    backLuz1.attachPush([]()
                        { updateTela(0); });
    adicionarSalaExtraLuz.attachPush([]()
                                     { addSalaExtra(0); });
    botaoLuzA1.attachPush([]()
                          {
        botaoLuzA1.getValue(&estadoLuzes[0][0]);
        serializeLampada(9, 0, estadoLuzes[0][0]); });
    botaoLuzB1.attachPush([]()
                          {
        botaoLuzB1.getValue(&estadoLuzes[0][1]);
        serializeLampada(9, 1, estadoLuzes[0][1]); });
    acenderTodasLuzes1.attachPush([]()
                                  { onOffTodasLuzes(1); });
    apagarTodasLuzes1.attachPush([]()
                                 { onOffTodasLuzes(0); });

    backLuz2.attachPush([]()
                        { updateTela(0); });
    removerSalaExtraLuz.attachPush([]()
                                   { removeSalaExtra(0); });
    botaoLuzA2.attachPush([]()
                          {
        botaoLuzA2.getValue(&estadoLuzes[0][0]);
        serializeLampada(10, 0, estadoLuzes[0][0]); });
    botaoLuzB2.attachPush([]()
                          {
        botaoLuzB2.getValue(&estadoLuzes[0][1]);
        serializeLampada(10, 1, estadoLuzes[0][1]); });
    botaoLuzC2.attachPush([]()
                          {
        botaoLuzC2.getValue(&estadoLuzes[1][0]);
        serializeLampada(10, 0, estadoLuzes[1][0]); });
    botaoLuzD2.attachPush([]()
                          {
        botaoLuzD2.getValue(&estadoLuzes[1][1]);
        serializeLampada(10, 1, estadoLuzes[1][1]); });
    acenderTodasLuzes2.attachPush([]()
                                  { onOffTodasLuzes(1); });
    apagarTodasLuzes2.attachPush([]()
                                 { onOffTodasLuzes(0); });

    // tela ar condicionado 3, 4
    backAc1.attachPush([]()
                       { updateTela(0); });
    adicionarSalaExtraAc.attachPush([]()
                                    { addSalaExtra(1); });

    selecionarAcA1.attachPush([]()
                              { selecionarAcA1.getValue(&acSelecionados[0]); });
    selecionarAcB1.attachPush([]()
                              { selecionarAcB1.getValue(&acSelecionados[1]); });
    botaoAcOnOff.attachPush([]()
                            { botaoAcOnOff.getValue(&estadoAc); });
    aumentarTempAc1.attachPush([]()
                               {temperaturaAc++;if(temperaturaAc > 30) temperaturaAc = 30;const char* tempStr = String(temperaturaAc).c_str(); textoTemp1.setText(tempStr); });
    diminuirTempAc1.attachPush([]()
                               {temperaturaAc--;if(temperaturaAc < 16) temperaturaAc = 16;const char* tempStr = String(temperaturaAc).c_str(); textoTemp1.setText(tempStr); });
    modoCoolAc1.attachPush([]()
                           {
        modoCoolAc1.getValue(&modoAc);
        if(modoAc) modoAc = 0;updateBotoesAc(0); });
    modoFanAc1.attachPush([]()
                          {
        modoFanAc1.getValue(&modoAc);
        if(modoAc) modoAc = 1;updateBotoesAc(0); });
    modoDryAc1.attachPush([]()
                          {
        modoDryAc1.getValue(&modoAc);
        if(modoAc) modoAc = 2;updateBotoesAc(0); });
    modoHeatAc1.attachPush([]()
                           {
        modoHeatAc1.getValue(&modoAc);
        if(modoAc) modoAc = 3;updateBotoesAc(0); });
    ventoAutoAc1.attachPush([]()
                            {
        ventoAutoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 0;updateBotoesAc(0); });
    ventoBaixoAc1.attachPush([]()
                             {
        ventoBaixoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 1;updateBotoesAc(0); });
    ventoMedioAc1.attachPush([]()
                             {
        ventoMedioAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 2;updateBotoesAc(0); });
    ventoAltoAc1.attachPush([]()
                            {
        ventoAltoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 3;updateBotoesAc(0); });
    ventoSilentAc1.attachPush([]()
                              {
        ventoSilentAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 4;updateBotoesAc(0); });
    confirmarConfigAc1.attachPush([]()
                                  {serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);updateBotoesAc(1); });

    backAc2.attachPush([]()
                       { updateTela(0); });
    removerSalaExtraAc.attachPush([]()
                                  { removeSalaExtra(1); });

    selecionarAcA2.attachPush([]()
                              { selecionarAcA2.getValue(&acSelecionados[0]); });
    selecionarAcB2.attachPush([]()
                              { selecionarAcB2.getValue(&acSelecionados[1]); });
    selecionarAcC2.attachPush([]()
                              { selecionarAcC2.getValue(&acSelecionados[2]); });
    selecionarAcD2.attachPush([]()
                              { selecionarAcD2.getValue(&acSelecionados[3]); });
    botaoAcOnOff2.attachPush([]()
                             { botaoAcOnOff2.getValue(&estadoAc); });
    aumentarTempAc2.attachPush([]()
                               {temperaturaAc++;if(temperaturaAc > 30) temperaturaAc = 30;const char* tempStr = String(temperaturaAc).c_str(); textoTemp2.setText(tempStr); });
    diminuirTempAc2.attachPush([]()
                               {temperaturaAc--;if(temperaturaAc < 16) temperaturaAc = 16;const char* tempStr = String(temperaturaAc).c_str(); textoTemp2.setText(tempStr); });
    modoCoolAc2.attachPush([](){
        modoCoolAc2.getValue(&modoAc);
        if(modoAc) modoAc = 0;updateBotoesAc(0); });
    modoFanAc2.attachPush([](){
        modoFanAc2.getValue(&modoAc);
        if(modoAc) modoAc = 1;updateBotoesAc(0); });
    modoDryAc2.attachPush([](){
        modoDryAc2.getValue(&modoAc);
        if(modoAc) modoAc = 2;updateBotoesAc(0); });
    modoHeatAc2.attachPush([](){
        modoHeatAc2.getValue(&modoAc);
        if(modoAc) modoAc = 3;updateBotoesAc(0); });
    ventoAutoAc2.attachPush([](){
        ventoAutoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 0;updateBotoesAc(0); });
    ventoBaixoAc2.attachPush([](){
        ventoBaixoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 1;updateBotoesAc(0); });
    ventoMedioAc2.attachPush([](){
        ventoMedioAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 2;updateBotoesAc(0); });
    ventoAltoAc2.attachPush([](){
        ventoAltoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 3;updateBotoesAc(0); });
    ventoSilentAc2.attachPush([](){
        ventoSilentAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 4;updateBotoesAc(0); });
    confirmarConfigAc2.attachPush([](){
        serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);
        updateBotoesAc(1); });

    //tela projetor 5, 6
    backProj1.attachPush([](){ updateTela(0); });
    adicionarSalaExtraProj.attachPush([](){ addSalaExtra(2); });

    telaRetratilUp1.attachPush([](){ serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop1.attachPush([](){ serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown1.attachPush([](){ serializeTelaRetratil(0, 1, 0); });
    projetorOnOff1.attachPush([](){
        projetorOnOff1.getValue(&estadoProjetor);
        serializeProjetor(estadoProjetor, false); });
    projetorFreeze1.attachPush([](){
        projetorFreeze1.getValue(&estadoFreezeProjetor);
        serializeProjetor(false, estadoFreezeProjetor); });
    backProj2.attachPush([](){ updateTela(0); });
    removerSalaExtraProj.attachPush([](){ removeSalaExtra(2); });
    selecionarProjetorA.attachPush([](){
        selecionarProjetorA.getValue(&projetoresSelecionados[0]);});
    selecionarProjetorB.attachPush([](){
        selecionarProjetorB.getValue(&projetoresSelecionados[1]);});
    telaRetratilUp2.attachPush([](){ serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop2.attachPush([](){ serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown2.attachPush([](){ serializeTelaRetratil(0, 1, 0); });
    projetorOnOff2.attachPush([](){
        projetorOnOff2.getValue(&estadoProjetor);
        serializeProjetor(estadoProjetor, false); });
    projetorFreeze2.attachPush([](){
        projetorFreeze2.getValue(&estadoFreezeProjetor);
        serializeProjetor(false, estadoFreezeProjetor); });

    //tela tv 7
    backTv.attachPush([](){ updateTela(0); });

    botaoTvOnOff.attachPush([](){
        serializeTv(1); });
    returnTv.attachPush([](){
        serializeTv(2); });
    aumentarVolumeTv.attachPush([](){
        serializeTv(3); });
    diminuirVolumeTv.attachPush([](){
        serializeTv(4); });
    dPadUpTv.attachPush([](){
        serializeTv(5); });
    dPadDownTv.attachPush([](){
        serializeTv(6); });
    dPadLeftTv.attachPush([](){
        serializeTv(7); });
    dPadRightTv.attachPush([](){
        serializeTv(8); });
    dPadSelectTv.attachPush([](){
        serializeTv(9); });

    //tela sensor 8
    backSensor.attachPush([](){ updateTela(0); });

    //tela settings 9
    backSettings.attachPush([](){ updateTela(0); });

   nexListen(telaLuz);
   nexListen(telaAc);
   nexListen(telaProj);
   nexListen(telaTv);
   nexListen(telaSensor);
   nexListen(telaSettings);

   nexListen(backLuz1);
   nexListen(adicionarSalaExtraLuz);
   nexListen(botaoLuzA1);
   nexListen(botaoLuzB1);
   nexListen(acenderTodasLuzes1);
   nexListen(apagarTodasLuzes1);
   nexListen(backLuz2);
   nexListen(removerSalaExtraLuz);
   nexListen(botaoLuzA2);
   nexListen(botaoLuzB2);
   nexListen(botaoLuzC2);
   nexListen(botaoLuzD2);
   nexListen(acenderTodasLuzes2);
   nexListen(apagarTodasLuzes2);
   nexListen(backAc1);
   nexListen(adicionarSalaExtraAc);
   nexListen(selecionarAcA1);
   nexListen(selecionarAcB1);
   nexListen(botaoAcOnOff);
   nexListen(aumentarTempAc1);
   nexListen(diminuirTempAc1);
   nexListen(modoCoolAc1);
   nexListen(modoFanAc1);
   nexListen(modoDryAc1);
   nexListen(modoHeatAc1);
   nexListen(ventoAutoAc1);
   nexListen(ventoBaixoAc1);
   nexListen(ventoMedioAc1);
   nexListen(ventoAltoAc1);
   nexListen(ventoSilentAc1);
   nexListen(confirmarConfigAc1);
   nexListen(backAc2);
   nexListen(removerSalaExtraAc);
   nexListen(selecionarAcA2);
   nexListen(selecionarAcB2);
   nexListen(selecionarAcC2);
   nexListen(selecionarAcD2);
   nexListen(botaoAcOnOff2);
   nexListen(aumentarTempAc2);
   nexListen(diminuirTempAc2);
   nexListen(modoCoolAc2);
   nexListen(modoFanAc2);
   nexListen(modoDryAc2);
   nexListen(modoHeatAc2);
   nexListen(ventoAutoAc2);
   nexListen(ventoBaixoAc2);
   nexListen(ventoMedioAc2);
   nexListen(ventoAltoAc2);
   nexListen(ventoSilentAc2);
   nexListen(confirmarConfigAc2);
   nexListen(backProj1);
   nexListen(adicionarSalaExtraProj);
   nexListen(telaRetratilUp1);
   nexListen(telaRetratilStop1);
   nexListen(telaRetratilDown1);
   nexListen(projetorOnOff1);
   nexListen(projetorFreeze1);
   nexListen(backProj2);
   nexListen(removerSalaExtraProj);
   nexListen(telaRetratilUp2);
   nexListen(telaRetratilStop2);
   nexListen(telaRetratilDown2);
   nexListen(projetorOnOff2);
   nexListen(projetorFreeze2);
   nexListen(backTv);
   nexListen(botaoTvOnOff);
   nexListen(returnTv);
   nexListen(aumentarVolumeTv);
   nexListen(diminuirVolumeTv);
   nexListen(dPadUpTv);
   nexListen(dPadDownTv);
   nexListen(dPadLeftTv);
   nexListen(dPadRightTv);
   nexListen(dPadSelectTv);
   nexListen(backSensor);
   nexListen(backSettings);

}

void updateTela(int modulo)
{
    switch (modulo)
    {
    case 0:
        sendCommand("page inicial");
        break;
    case 1:
        if (luzSalaExtra)
            sendCommand("page luz1");
        else
            sendCommand("page luz0");
        break;
    case 2:
        if (arSalaExtra)
            sendCommand("page ac1");
        else
            sendCommand("page ac0");
        break;
    case 3:
        if (projSalaExtra)
            sendCommand("page proj1");
        else
            sendCommand("page proj0");
        break;
    case 4:
        sendCommand("page tv");
        break;
    case 5:
        sendCommand("page sensores");
        break;
    case 6:
        sendCommand("page settings");
        break;
    }
}

void addSalaExtra(int modulo)
{
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 1;
        updateTela(1);
        break;
    case 1:
        arSalaExtra = 1;
        updateTela(2);
        break;
    case 2:
        projSalaExtra = 1;
        updateTela(3);
        break;
    }
}

void removeSalaExtra(int modulo)
{
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 0;
        updateTela(1);
        break;
    case 1:
        arSalaExtra = 0;
        updateTela(2);
        break;
    case 2:
        projSalaExtra = 0;
        updateTela(3);
        break;
    }
}

void deserializeModuloAnalise(const String &mensagem)
{
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        debugError("Json inválido, corrigir formatação");
        return;
    }

    if (doc["analise"].is<JsonVariant>())
    {
        if (!doc["analise"]["timestamp"].as<u_long>() || !doc["analise"]["temperatura"].as<float>() || !doc["analise"]["umidade"].as<float>() || doc["analise"]["ruido"].as<float>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["comandoAr"].as<int>() || doc["analise"]["alertaSom"].as<int>() || doc["analise"]["eco"].as<bool>())
        {
            debugError("Json invalido");
            return;
        }
    }
    else
    {
        timeStampAnalise = doc["analise"]["timestamp"].as<u_long>();
        temperatura = doc["analise"]["temperatura"].as<float>();
        umidade = doc["analise"]["umidade"].as<float>();
        ruido = doc["analise"]["ruido"].as<float>();
        comandoAr = doc["analise"]["comandoAr"].as<int>();
        alerta = doc["analise"]["alertaSom"].as<int>();
        eco = doc["analise"]["eco"].as<bool>();

        debugInfo("Analise desserializada com sucesso:");
        debugInfo("Timestamp: " + String(timeStampAnalise));

        sprintf(buffer, "%.1f", temperatura);
        textoTempLadoA.setText(buffer);

        sprintf(buffer, "%.1f", umidade);
        textoUmidadeLadoA.setText(buffer);

        sprintf(buffer, "%.1f", ruido);
        textoRuidoLadoA.setText(buffer);

        sprintf(buffer, "%s", alerta ? "Alerta!" : "Normal");
        textoAmbienteSensor.setText(buffer);
    }
}

void updateBotoesAc(bool confirmado)
{
    if (!arSalaExtra)
    {
        modoCoolAc1.setValue(0);
        modoFanAc1.setValue(0);
        modoDryAc1.setValue(0);
        modoHeatAc1.setValue(0);
        ventoAutoAc1.setValue(0);
        ventoBaixoAc1.setValue(0);
        ventoMedioAc1.setValue(0);
        ventoAltoAc1.setValue(0);
        ventoSilentAc1.setValue(0);
        if (confirmado)
        {
            return;
        }
        switch (modoAc)
        {
        case 0:
            modoCoolAc1.setValue(1);
            break;
        case 1:
            modoFanAc1.setValue(1);
            break;
        case 2:
            modoDryAc1.setValue(1);
            break;
        case 3:
            modoHeatAc1.setValue(1);
            break;
        }
        switch (ventoAc)
        {
        case 0:
            ventoAutoAc1.setValue(1);
            break;
        case 1:
            ventoBaixoAc1.setValue(1);
            break;
        case 2:
            ventoMedioAc1.setValue(1);
            break;
        case 3:
            ventoAltoAc1.setValue(1);
            break;
        case 4:
            ventoSilentAc1.setValue(1);
            break;
        }
    }
    else
    {
        modoCoolAc2.setValue(0);
        modoFanAc2.setValue(0);
        modoDryAc2.setValue(0);
        modoHeatAc2.setValue(0);
        ventoAutoAc2.setValue(0);
        ventoBaixoAc2.setValue(0);
        ventoMedioAc2.setValue(0);
        ventoAltoAc2.setValue(0);
        ventoSilentAc2.setValue(0);
        if (confirmado)
        {
            return;
        }
        switch (modoAc)
        {
        case 0:
            modoCoolAc2.setValue(1);
            break;
        case 1:
            modoFanAc2.setValue(1);
            break;
        case 2:
            modoDryAc2.setValue(1);
            break;
        case 3:
            modoHeatAc2.setValue(1);
            break;
        }
        switch (ventoAc)
        {
        case 0:
            ventoAutoAc2.setValue(1);
            break;
        case 1:
            ventoBaixoAc2.setValue(1);
            break;
        case 2:
            ventoMedioAc2.setValue(1);
            break;
        case 3:
            ventoAltoAc2.setValue(1);
            break;
        case 4:
            ventoSilentAc2.setValue(1);
            break;
        }
    }
}