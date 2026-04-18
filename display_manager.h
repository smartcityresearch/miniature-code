#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include <Arduino.h>

void displayInit();
void displayUpdate(int c1, int c2, int c3, int c4);
void displayShowOtaProgress(int progress);
void displayShowIP(String ip);

#endif