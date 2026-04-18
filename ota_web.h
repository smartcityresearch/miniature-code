#ifndef OTA_WEB_H
#define OTA_WEB_H

#include <Arduino.h>

// Init web server
void otaWebInit();

// Handle client (call in loop)
void otaWebHandle();

// Update values from OTA
void otaWebSetCurrentVersion(int version);
void otaWebSetRemoteVersion(int version);
void otaWebSetProgress(int progress);
void otaWebSetStatus(String status);

#endif