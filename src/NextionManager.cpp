#include <Arduino.h>
#include <Nextion.h>
#include "DisplayButtons.h"
#include "NextionManager.h"
#include "Serialize.h"
#include <ArduinoJson.h>
#include "DebugManager.h"

// =========================================================
// Variaveis de estado dos módulos e da tela
// =========================================================

uint8_t acaoTv;

uint32_t estadoLuzes[2][2] = {{0, 0}, {0, 0}};
int tela = 0;

float temperaturaA;
float umidadeA;
float ruidoA;
int alertaA;
float temperaturaB;
float umidadeB;
float ruidoB;
int alertaB;
int comandoAr;
bool eco;
u_long timeStampAnalise;
char buffer[100];

uint32_t estadoAc = 0;
int temperaturaAc = 24;
uint32_t modoAc = 0;
uint32_t ventoAc = 4;

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
    sendCommand("dim=100");
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
        serializeLampada(9, 1, estadoLuzes[0][0]); });
    botaoLuzB1.attachPush([]()
                         {
        botaoLuzB1.getValue(&estadoLuzes[0][1]);
        serializeLampada(9, 0, estadoLuzes[0][1]); });
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
        serializeLampada(9, 1, estadoLuzes[0][0]); });
    botaoLuzB2.attachPush([]()
                         {
        botaoLuzB2.getValue(&estadoLuzes[0][1]);
        serializeLampada(9, 0, estadoLuzes[0][1]); });
    botaoLuzC2.attachPush([]()
                         {
        botaoLuzC2.getValue(&estadoLuzes[1][0]);
        serializeLampada(10, 1, estadoLuzes[1][0]); });
    botaoLuzD2.attachPush([]()
                         {
        botaoLuzD2.getValue(&estadoLuzes[1][1]);
        serializeLampada(10, 0, estadoLuzes[1][1]); });
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
                              {
    temperaturaAc++;
    if (temperaturaAc > 30) temperaturaAc = 30;
    char bufTemp[8];
    sprintf(bufTemp, "%d", temperaturaAc);
    textoTemp1.setText(bufTemp); });
    diminuirTempAc1.attachPush([]()
                              {
    temperaturaAc--;
    if (temperaturaAc < 16) temperaturaAc = 16;
    char bufTemp[8];
    sprintf(bufTemp, "%d", temperaturaAc);
    textoTemp1.setText(bufTemp); });
 modoCoolAc1.attachPush([](){
    modoAc = 0;
    updateBotoesAc(0);
});
modoFanAc1.attachPush([](){
    modoAc = 2;
    updateBotoesAc(0);
});
modoDryAc1.attachPush([](){
    modoAc = 1;
    updateBotoesAc(0);
});
modoHeatAc1.attachPush([](){
    modoAc = 3;
    updateBotoesAc(0);
});
    ventoAutoAc1.attachPush([](){   ventoAc = 0; updateBotoesAc(0); });
ventoBaixoAc1.attachPush([](){  ventoAc = 2; updateBotoesAc(0); });
ventoMedioAc1.attachPush([](){  ventoAc = 3; updateBotoesAc(0); });
ventoAltoAc1.attachPush([](){   ventoAc = 4; updateBotoesAc(0); });
ventoSilentAc1.attachPush([](){  ventoAc = 1; updateBotoesAc(0); });
    confirmarConfigAc1.attachPush([]()
                                 {botaoAcOnOff.getValue(&estadoAc);
    serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);
    updateBotoesAc(1);});

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
    aumentarTempAc2.attachPush([](){
    temperaturaAc++;
    if (temperaturaAc > 30) temperaturaAc = 30;
    char bufTemp[8];
    sprintf(bufTemp, "%d", temperaturaAc);
    textoTemp2.setText(bufTemp);
});
diminuirTempAc2.attachPush([](){
    temperaturaAc--;
    if (temperaturaAc < 16) temperaturaAc = 16;
    char bufTemp[8];
    sprintf(bufTemp, "%d", temperaturaAc);
    textoTemp2.setText(bufTemp);
});
    modoCoolAc2.attachPush([](){  modoAc = 0; updateBotoesAc(0); });
    modoDryAc2.attachPush([](){   modoAc = 1; updateBotoesAc(0); });
modoFanAc2.attachPush([](){   modoAc = 2; updateBotoesAc(0); });
modoHeatAc2.attachPush([](){  modoAc = 3; updateBotoesAc(0); });
    ventoAutoAc2.attachPush([](){    ventoAc = 0; updateBotoesAc(0); });
ventoBaixoAc2.attachPush([](){   ventoAc = 2; updateBotoesAc(0); });
ventoMedioAc2.attachPush([](){   ventoAc = 3; updateBotoesAc(0); });
ventoAltoAc2.attachPush([](){    ventoAc = 4; updateBotoesAc(0); });
ventoSilentAc2.attachPush([](){  ventoAc = 1; updateBotoesAc(0); });
    confirmarConfigAc2.attachPush([]()
                                 {
        botaoAcOnOff2.getValue(&estadoAc);
    serializeAc(estadoAc, temperaturaAc, modoAc, ventoAc);
    updateBotoesAc(1);});

    // tela projetor 5, 6
    backProj1.attachPush([]()
                        { updateTela(0); });
    adicionarSalaExtraProj.attachPush([]()
                                     { addSalaExtra(2); });

    telaRetratilUp1.attachPush([]()
                              { serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop1.attachPush([]()
                                { serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown1.attachPush([]()
                                { serializeTelaRetratil(0, 1, 0); });
    projetorFreeze1.attachPush([]()
                              {
    projetorFreeze1.getValue(&estadoProjFreeze[0]);
    if (estadoProj[0] == 0)                
    {
        estadoProjFreeze[0] = 0;         
        projetorFreeze1.setValue(0);     
        debugInfo("Freeze ignorado: projetor 1 desligado");
        return;
    }
    serializeProjetor(estadoProj[0], estadoProjFreeze[0]); });

    projetorFreeze2.attachPush([]()
                              {
    projetorFreeze2.getValue(&estadoProjFreeze[1]);
    if (estadoProj[1] == 0)
    {
        estadoProjFreeze[1] = 0;
        projetorFreeze2.setValue(0);
        debugInfo("Freeze ignorado: projetor 2 desligado");
        return;
    }
    serializeProjetor(estadoProj[1], estadoProjFreeze[1]); });

    projetorOnOff1.attachPush([]()
                             {
    projetorOnOff1.getValue(&estadoProj[0]);
    if (estadoProj[0] == 0)            
    {
        estadoProjFreeze[0] = 0;
        projetorFreeze1.setValue(0);
    }
    serializeProjetor(estadoProj[0], estadoProjFreeze[0]); });

    projetorOnOff2.attachPush([]()
                             {
    projetorOnOff2.getValue(&estadoProj[1]);
    if (estadoProj[1] == 0)
    {
        estadoProjFreeze[1] = 0;
        projetorFreeze2.setValue(0);
    }
    serializeProjetor(estadoProj[1], estadoProjFreeze[1]); });
    backProj2.attachPush([]()
                        { updateTela(0); });
    removerSalaExtraProj.attachPush([]()
                                   { removeSalaExtra(2); });
    selecionarProjetorA.attachPush([]()
                                  { selecionarProjetorA.getValue(&projetoresSelecionados[0]); Serial.printf("Projetor A:%d", projetoresSelecionados[0]); });
    selecionarProjetorB.attachPush([]()
                                  { selecionarProjetorB.getValue(&projetoresSelecionados[1]); Serial.printf("Projetor B:%d", projetoresSelecionados[1]); });
    telaRetratilUp2.attachPush([]()
                              { serializeTelaRetratil(1, 0, 0); });
    telaRetratilStop2.attachPush([]()
                                { serializeTelaRetratil(0, 0, 1); });
    telaRetratilDown2.attachPush([]()
                                { serializeTelaRetratil(0, 1, 0); });

    // tela tv 7
    backTv.attachPush([]()
                     { updateTela(0); });

    botaoTvOnOff.attachPush([]()
                           { serializeTv(1); });
    returnTv.attachPush([]()
                       { serializeTv(9); });
    aumentarVolumeTv.attachPush([]()
                               { serializeTv(2); });
    diminuirVolumeTv.attachPush([]()
                               { serializeTv(3); });
    dPadUpTv.attachPush([]()
                       { serializeTv(6); });
    dPadDownTv.attachPush([]()
                         { serializeTv(7); });
    dPadLeftTv.attachPush([]()
                         { serializeTv(5); });
    dPadRightTv.attachPush([]()
                          { serializeTv(4); });
    dPadSelectTv.attachPush([]()
                           { serializeTv(8); });

    // tela sensor 8
    backSensor.attachPush([]()
                         { updateTela(0); });

    // tela settings 9
    backSettings.attachPush([]()
                           { updateTela(0); });

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
    nexListen(selecionarProjetorB);
    nexListen(selecionarProjetorA);
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
    prefs.begin("config", false);
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 1;
        prefs.putBool("luzExtra", true);
        break;
    case 1:
        arSalaExtra = 1;
        prefs.putBool("arExtra", true);
        break;
    case 2:
        projSalaExtra = 1;
        prefs.putBool("projExtra", true);
        break;
    }
    prefs.end();
    updateTela(modulo + 1);
}

void removeSalaExtra(int modulo)
{
    prefs.begin("config", false);
    switch (modulo)
    {
    case 0:
        luzSalaExtra = 0;
        prefs.putBool("luzExtra", false);
        break;
    case 1:
        arSalaExtra = 0;
        prefs.putBool("arExtra", false);
        break;
    case 2:
        projSalaExtra = 0;
        prefs.putBool("projExtra", false);
        break;
    }
    prefs.end();
    updateTela(modulo + 1);
}

void deserializeModuloAnalise(const String &mensagem)
{
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, mensagem);
    if (erro)
    {
        debugErro("Json inválido");
        return;
    }

    if (!doc["analise"].is<JsonObject>())
    {
        debugErro("Campo 'analise' ausente no JSON");
        return;
    }

    JsonObject analise = doc["analise"];
    if (analise["timestamp"].isNull())
    {
        debugErro("Json incompleto — campo ausente");
        return;
    }

    timeStampAnalise = analise["timestamp"].as<u_long>();
    temperaturaA = analise["temperatura"].as<float>();
    umidadeA = analise["umidade"].as<float>();
    ruidoA = analise["ruido"].as<float>();
    comandoAr = analise["comandoAr"].as<int>();
    alertaA = analise["alertaSom"].as<int>();
    eco = analise["eco"].as<bool>();

    debugInfo("Analise desserializada: timestamp=" + String(timeStampAnalise));

    char buf[20];

    if(temperaturaA > 0){
    sprintf(buf, "%.1f", temperaturaA);
    textoTempLadoA.setText(buf);}
    
    if(umidadeA > 0){
    sprintf(buf, "%.1f", umidadeA);
    textoUmidadeLadoA.setText(buf);}
    
    sprintf(buf, "%.1f", ruidoA);
    textoRuidoLadoA.setText(buf);

    if(alertaA && alertaB)
    textoAmbienteSensor.setText("Alerta!");
    else
    textoAmbienteSensor.setText("Normal");
}

void deserializeModuloAnaliseB(const String &mensagem)
{
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, mensagem);
    if (erro)
    {
        debugErro("Json inválido");
        return;
    }

    if (!doc["analise"].is<JsonObject>())
    {
        debugErro("Campo 'analise' ausente no JSON");
        return;
    }

    JsonObject analise = doc["analise"];
    if (analise["timestamp"].isNull())
    {
        debugErro("Json incompleto — campo ausente");
        return;
    }

    timeStampAnalise = analise["timestamp"].as<u_long>();
    temperaturaB = analise["temperatura"].as<float>();
    umidadeB = analise["umidade"].as<float>();
    ruidoB = analise["ruido"].as<float>();
    comandoAr = analise["comandoAr"].as<int>();
    alertaB = analise["alertaSom"].as<int>();
    eco = analise["eco"].as<bool>();

    debugInfo("Analise desserializada: timestamp=" + String(timeStampAnalise));

    char buf[20];

    if(temperaturaB > 0){
    sprintf(buf, "%.1f", temperaturaB);
    textoTempLadoB.setText(buf);}
    
    if(umidadeB > 0){
    sprintf(buf, "%.1f", umidadeB);
    textoUmidadeLadoB.setText(buf);}
    
    sprintf(buf, "%.1f", ruidoB);
    textoRuidoLadoB.setText(buf);

    if(alertaA && alertaB)
    textoAmbienteSensor.setText("Alerta!");
    else
    textoAmbienteSensor.setText("Normal");

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
            botaoAcOnOff.setValue(0);
            acSelecionados[0] = 0;
            acSelecionados[1] = 0;

            estadoAc = 0;
            modoAc = 0;
            ventoAc = 4;
            temperaturaAc = 24;
            return;
        }
        switch (modoAc)
        {
        case 0:
            modoCoolAc1.setValue(1);
            break;
        case 1:
        modoDryAc1.setValue(1);
        break;
        case 2:
        modoFanAc1.setValue(1);
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
        ventoSilentAc1.setValue(1);
        break;
        case 2:
        ventoBaixoAc1.setValue(1);
        break;
        case 3:
        ventoMedioAc1.setValue(1);
        break;
        case 4:
        ventoAltoAc1.setValue(1);
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
            botaoAcOnOff2.setValue(0);
            acSelecionados[0] = 0;
            acSelecionados[1] = 0;
            acSelecionados[2] = 0;
            acSelecionados[3] = 0;

            estadoAc = 0;
            modoAc = 0;
            ventoAc = 4;
            temperaturaAc = 24;
            return;
        }
        switch (modoAc)
        {
        case 0:
            modoCoolAc2.setValue(1);
            break;
        case 1:
        modoDryAc2.setValue(1);
        break;
        case 2:
        modoFanAc2.setValue(1);
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
        ventoSilentAc2.setValue(1);
        break;
        case 2:
        ventoBaixoAc2.setValue(1);
        break;
        case 3:
        ventoMedioAc2.setValue(1);
        break;
        case 4:
        ventoAltoAc2.setValue(1);
            break;
        }
    }
}
