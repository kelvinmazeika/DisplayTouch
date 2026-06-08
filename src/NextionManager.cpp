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
uint32_t modoAc = 10;
uint32_t ventoAc = 10;

uint32_t estadoProjetor = 0;
uint32_t estadoFreezeProjetor = 0;
uint32_t estadoProjetor2 = 0;
uint32_t estadoFreezeProjetor2 = 0;


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
    sendCommand("bkcmd=0");
    delay(100);
}

void configurarEventosNextion()
{
    // tela inicial 0
    telaLuz.attachPop([](){updateTela(1);});
    telaAc.attachPop([]()
                      { updateTela(2); });
    telaProj.attachPop([]()
                        { updateTela(3); });
    telaTv.attachPop([]()
                      { updateTela(4); });
    telaSensor.attachPop([]()
                          { updateTela(5); });
    telaSettings.attachPop([]()
                            { updateTela(6); });

    // tela luz 1, 2
    backLuz1.attachPop([]()
                        { updateTela(0); });
    adicionarSalaExtraLuz.attachPop([]()
                                     { addSalaExtra(0); });
    botaoLuzA1.attachPop([]()
                          {
        botaoLuzA1.getValue(&estadoLuzes[0][0]);
        serializeLampada(9, 0, estadoLuzes[0][0]); });
    botaoLuzB1.attachPop([]()
                          {
        botaoLuzB1.getValue(&estadoLuzes[0][1]);
        serializeLampada(9, 1, estadoLuzes[0][1]); });
    acenderTodasLuzes1.attachPop([]()
                                  { onOffTodasLuzes(1); });
    apagarTodasLuzes1.attachPop([]()
                                 { onOffTodasLuzes(0); });

    backLuz2.attachPop([]()
                        { updateTela(0); });
    removerSalaExtraLuz.attachPop([]()
                                   { removeSalaExtra(0); });
    botaoLuzA2.attachPop([]()
                          {
        botaoLuzA2.getValue(&estadoLuzes[0][0]);
        serializeLampada(9, 0, estadoLuzes[0][0]); });
    botaoLuzB2.attachPop([]()
                          {
        botaoLuzB2.getValue(&estadoLuzes[0][1]);
        serializeLampada(9, 1, estadoLuzes[0][1]); });
    botaoLuzC2.attachPop([]()
                          {
        botaoLuzC2.getValue(&estadoLuzes[1][0]);
        serializeLampada(10, 0, estadoLuzes[1][0]); });
    botaoLuzD2.attachPop([]()
                          {
        botaoLuzD2.getValue(&estadoLuzes[1][1]);
        serializeLampada(10, 1, estadoLuzes[1][1]); });
    acenderTodasLuzes2.attachPop([]()
                                  { onOffTodasLuzes(1); });
    apagarTodasLuzes2.attachPop([]()
                                 { onOffTodasLuzes(0); });

    // tela ar condicionado 3, 4
    backAc1.attachPop([]()
                       { updateTela(0); });
    adicionarSalaExtraAc.attachPop([]()
                                    { addSalaExtra(1); });

    selecionarAcA1.attachPop([]()
                              { selecionarAcA1.getValue(&acSelecionados[0]); });
    selecionarAcB1.attachPop([]()
                              { selecionarAcB1.getValue(&acSelecionados[1]); });
    botaoAcOnOff.attachPop([]()
                            { botaoAcOnOff.getValue(&estadoAc); });
    aumentarTempAc1.attachPop([]()
                               {temperaturaAc++;if(temperaturaAc > 30) temperaturaAc = 30;const char* tempStr = String(temperaturaAc).c_str(); textoTemp1.setText(tempStr); });
    diminuirTempAc1.attachPop([]()
                               {temperaturaAc--;if(temperaturaAc < 16) temperaturaAc = 16;const char* tempStr = String(temperaturaAc).c_str(); textoTemp1.setText(tempStr); });
    modoCoolAc1.attachPop([]()
                           {
        modoCoolAc1.getValue(&modoAc);
        if(modoAc) modoAc = 0;updateBotoesAc(0); });
    modoFanAc1.attachPop([]()
                          {
        modoFanAc1.getValue(&modoAc);
        if(modoAc) modoAc = 1;updateBotoesAc(0); });
    modoDryAc1.attachPop([]()
                          {
        modoDryAc1.getValue(&modoAc);
        if(modoAc) modoAc = 2;updateBotoesAc(0); });
    modoHeatAc1.attachPop([]()
                           {
        modoHeatAc1.getValue(&modoAc);
        if(modoAc) modoAc = 3;updateBotoesAc(0); });
    ventoAutoAc1.attachPop([]()
                            {
        ventoAutoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 0;updateBotoesAc(0); });
    ventoBaixoAc1.attachPop([]()
                             {
        ventoBaixoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 1;updateBotoesAc(0); });
    ventoMedioAc1.attachPop([]()
                             {
        ventoMedioAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 2;updateBotoesAc(0); });
    ventoAltoAc1.attachPop([]()
                            {
        ventoAltoAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 3;updateBotoesAc(0); });
    ventoSilentAc1.attachPop([]()
                              {
        ventoSilentAc1.getValue(&ventoAc);
        if(ventoAc) ventoAc = 4;updateBotoesAc(0); });
    confirmarConfigAc1.attachPop([]()
                                  {serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);updateBotoesAc(1); });

    backAc2.attachPop([]()
                       { updateTela(0); });
    removerSalaExtraAc.attachPop([]()
                                  { removeSalaExtra(1); });

    selecionarAcA2.attachPop([]()
                              { selecionarAcA2.getValue(&acSelecionados[0]); });
    selecionarAcB2.attachPop([]()
                              { selecionarAcB2.getValue(&acSelecionados[1]); });
    selecionarAcC2.attachPop([]()
                              { selecionarAcC2.getValue(&acSelecionados[2]); });
    selecionarAcD2.attachPop([]()
                              { selecionarAcD2.getValue(&acSelecionados[3]); });
    botaoAcOnOff2.attachPop([]()
                             { botaoAcOnOff2.getValue(&estadoAc); });
    aumentarTempAc2.attachPop([]()
                               {temperaturaAc++;if(temperaturaAc > 30) temperaturaAc = 30;const char* tempStr = String(temperaturaAc).c_str(); textoTemp2.setText(tempStr); });
    diminuirTempAc2.attachPop([]()
                               {temperaturaAc--;if(temperaturaAc < 16) temperaturaAc = 16;const char* tempStr = String(temperaturaAc).c_str(); textoTemp2.setText(tempStr); });
    modoCoolAc2.attachPop([](){
        modoCoolAc2.getValue(&modoAc);
        if(modoAc) modoAc = 0;updateBotoesAc(0); });
    modoFanAc2.attachPop([](){
        modoFanAc2.getValue(&modoAc);
        if(modoAc) modoAc = 1;updateBotoesAc(0); });
    modoDryAc2.attachPop([](){
        modoDryAc2.getValue(&modoAc);
        if(modoAc) modoAc = 2;updateBotoesAc(0); });
    modoHeatAc2.attachPop([](){
        modoHeatAc2.getValue(&modoAc);
        if(modoAc) modoAc = 3;updateBotoesAc(0); });
    ventoAutoAc2.attachPop([](){
        ventoAutoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 0;updateBotoesAc(0); });
    ventoBaixoAc2.attachPop([](){
        ventoBaixoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 1;updateBotoesAc(0); });
    ventoMedioAc2.attachPop([](){
        ventoMedioAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 2;updateBotoesAc(0); });
    ventoAltoAc2.attachPop([](){
        ventoAltoAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 3;updateBotoesAc(0); });
    ventoSilentAc2.attachPop([](){
        ventoSilentAc2.getValue(&ventoAc);
        if(ventoAc) ventoAc = 4;updateBotoesAc(0); });
    confirmarConfigAc2.attachPop([](){
        serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);
        updateBotoesAc(1); });

    //tela projetor 5, 6
    backProj1.attachPop([](){ updateTela(0); });
    adicionarSalaExtraProj.attachPop([](){ addSalaExtra(2); });

    telaRetratilUp1.attachPop([](){ serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop1.attachPop([](){ serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown1.attachPop([](){ serializeTelaRetratil(0, 1, 0); });
    projetorOnOff1.attachPop([](){
        projetorOnOff1.getValue(&estadoProjetor);
        serializeProjetor(estadoProjetor, false); });
    projetorFreeze1.attachPop([](){
        projetorFreeze1.getValue(&estadoFreezeProjetor);
        serializeProjetor(false, estadoFreezeProjetor); });
    backProj2.attachPop([](){ updateTela(0); });
    removerSalaExtraProj.attachPop([](){ removeSalaExtra(2); });
    selecionarProjetorA.attachPop([](){
        selecionarProjetorA.getValue(&projetoresSelecionados[0]);});
    selecionarProjetorB.attachPop([](){
        selecionarProjetorB.getValue(&projetoresSelecionados[1]);});
    telaRetratilUp2.attachPop([](){ serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop2.attachPop([](){ serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown2.attachPop([](){ serializeTelaRetratil(0, 1, 0); });
    projetorOnOff2.attachPop([](){
        projetorOnOff2.getValue(&estadoProjetor2);
        serializeProjetor(estadoProjetor2, false); });
    projetorFreeze2.attachPop([](){
        projetorFreeze2.getValue(&estadoFreezeProjetor2);
        serializeProjetor(false, estadoFreezeProjetor2);});

    //tela tv 7
    backTv.attachPop([](){ updateTela(0); });

    botaoTvOnOff.attachPop([](){
        serializeTv(1); });
    returnTv.attachPop([](){
        serializeTv(9); });
    aumentarVolumeTv.attachPop([](){
        serializeTv(2); });
    diminuirVolumeTv.attachPop([](){
        serializeTv(3); });
    dPadUpTv.attachPop([](){
        serializeTv(6); });
    dPadDownTv.attachPop([](){
        serializeTv(7); });
    dPadLeftTv.attachPop([](){
        serializeTv(5); });
    dPadRightTv.attachPop([](){
        serializeTv(4); });
    dPadSelectTv.attachPop([](){
        serializeTv(8); });

    //tela sensor 8
    backSensor.attachPop([](){ updateTela(0); });

    //tela settings 9
    backSettings.attachPop([](){ updateTela(0); });

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
            sendCommand("page projetor1");
        else
            sendCommand("page projetor0");
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
        if (doc["analise"]["timestamp"].isNull() || doc["analise"]["temperatura"].isNull() || doc["analise"]["umidade"].isNull() || doc["analise"]["ruido"].isNull() || doc["analise"]["comandoAr"].isNull() || doc["analise"]["comandoAr"].isNull() || doc["analise"]["alertaSom"].isNull() || doc["analise"]["eco"].isNull())
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
void deserializeModuloAnaliseB(const String &mensagem)
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
        if (doc["analise"]["timestamp"].isNull() || doc["analise"]["temperatura"].isNull() || doc["analise"]["umidade"].isNull() || doc["analise"]["ruido"].isNull() || doc["analise"]["comandoAr"].isNull() || doc["analise"]["comandoAr"].isNull() || doc["analise"]["alertaSom"].isNull() || doc["analise"]["eco"].isNull())
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
        textoTempLadoB.setText(buffer);

        sprintf(buffer, "%.1f", umidade);
        textoUmidadeLadoB.setText(buffer);

        sprintf(buffer, "%.1f", ruido);
        textoRuidoLadoB.setText(buffer);

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
            modoAc = 10;
            ventoAc = 10;
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
            modoAc = 10;
            ventoAc = 10;
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

void teste()
{
    Serial.println("detectou");
}