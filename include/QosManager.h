#ifndef QOSMANAGER_H
#define QOSMANAGER_H
#pragma once
#include <Arduino.h>

void qosPublicar(const char* topico, const char* payload, u_long timestamp);
void qosConfirmar(u_long timestamp);
void qosLoop();

#endif