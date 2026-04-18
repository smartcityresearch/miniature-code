#include "wifi_manager.h"
#include <WiFi.h>
#include "display_manager.h"

void wifiInit(const char *ssid, const char *password)
{

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    // ⏱ Timeout after 10 sec
    if (millis() - startTime > 10000)
    {
      Serial.println("\nWiFi Timeout!");
      return;
    }
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  displayShowIP(WiFi.localIP().toString());
  delay(3000);
}

bool wifiIsConnected()
{
  return WiFi.status() == WL_CONNECTED;
}