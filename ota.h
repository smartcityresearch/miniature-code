#ifndef OTA_H
#define OTA_H

#include <Arduino.h>

void otaInit();
void otaHandle(bool forceCheck = false);
void otaSetVersion(int version);
void otaSetUrls(String versionUrl, String firmwareUrl);

#endif