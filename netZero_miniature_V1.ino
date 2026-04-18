#include "config.h"
#include "wifi_manager.h"
#include "ota.h"
#include "display_manager.h"
#include "relay_manager.h"
#include "led_manager.h"
#include "ota_web.h"
int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
unsigned long lastOTACheck = 0;

void setup()
{

  Serial.begin(115200);

  displayInit();

  wifiInit(WIFI_SSID, WIFI_PASSWORD);

  otaSetVersion(CURRENT_VERSION);
  otaSetUrls(VERSION_URL, FIRMWARE_URL);
  otaInit();
  otaHandle(true);

  relayInit();
  ledInit();
  otaWebInit();
  otaWebSetCurrentVersion(CURRENT_VERSION);
  pinMode(SOLAR_SW, INPUT_PULLUP);
  pinMode(RAIN_SW, INPUT_PULLUP);
  pinMode(STP_SW, INPUT_PULLUP);
  pinMode(GRID_SW, INPUT_PULLUP);
  pinMode(BOREWELL_SW, INPUT_PULLUP);

  pinMode(GRID_LED, OUTPUT);
  pinMode(SOLAR_LED, OUTPUT);
}

void loop()
{
  otaWebHandle();
  if (millis() - lastOTACheck >= OTA_CHECK_INTERVAL)
  {
    lastOTACheck = millis();
    otaHandle();
  }

  if (digitalRead(SOLAR_SW) == LOW)
  {
    count1++;
    digitalWrite(SOLAR_LED, HIGH);
    setCarbon(0, 100);
  }
  else if (digitalRead(RAIN_SW) == LOW)
  {
    count2++;
    relayControl(1, 0, 0, 0);
    setCarbon(60, 40);
  }
  else if (digitalRead(STP_SW) == LOW)
  {
    count3++;
    relayControl(0, 1, 0, 0);
    setCarbon(50, 50);
  }

  else if (digitalRead(GRID_SW) == LOW)
  {
    count4++;
    digitalWrite(GRID_LED, HIGH);
    setCarbon(80, 20);
  }

  else if (digitalRead(BOREWELL_SW) == LOW)
  {
    relayControl(0, 0, 1, 0);
    setCarbon(70, 30);
  }

  displayUpdate(count1, count2, count3, count4);
  delay(20);
}