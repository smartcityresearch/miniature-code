#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

void wifiInit(const char* ssid, const char* password);
bool wifiIsConnected();

#endif