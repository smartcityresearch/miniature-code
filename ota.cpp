#include "ota.h"
#include "wifi_manager.h"
#include "display_manager.h"
#include "config.h"
#include "WiFi.h"
#include <HTTPClient.h>
#include <Update.h>
#include <WiFiClientSecure.h>
#include "ota_web.h"

static String _versionUrl;
static String _firmwareUrl;
static int _currentVersion = 0;

static unsigned long lastOTACheck = 0;

void performOTA(); // forward declaration

// ---------------- SETTERS ----------------

void otaSetVersion(int version)
{
  _currentVersion = version;
  otaWebSetCurrentVersion(version); // ✅ update web
}

void otaSetUrls(String versionUrl, String firmwareUrl)
{
  _versionUrl = versionUrl;
  _firmwareUrl = firmwareUrl;
}

// ---------------- INIT ----------------

void otaInit()
{
  Serial.println("OTA Init Done");
  otaWebSetStatus("Idle"); // ✅ initial state
  otaWebSetProgress(0);
}

// ---------------- HANDLE ----------------

void otaHandle(bool forceCheck)
{
  if (!forceCheck && (millis() - lastOTACheck < OTA_CHECK_INTERVAL))
    return;

  lastOTACheck = millis();

  if (!wifiIsConnected())
    return;

  Serial.println("\nChecking for OTA update...");
  otaWebSetStatus("Checking...");

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, _versionUrl);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK)
  {
    String payload = http.getString();
    payload.trim();

    Serial.println("Raw response: [" + payload + "]");

    int latestVersion = atoi(payload.c_str());

    otaWebSetRemoteVersion(latestVersion); // ✅ important
    if (forceCheck)
    {
      displayShowVersions(_currentVersion, latestVersion);
      delay(2000);
    }

    Serial.println("Current Version: " + String(_currentVersion));
    Serial.println("Latest Version: " + String(latestVersion));

    if (latestVersion > _currentVersion)
    {
      Serial.println("Update Available!");
      otaWebSetStatus("Updating...");
      performOTA();
    }
    else
    {
      Serial.println("No Update Available.");
      otaWebSetStatus("Up-to-date");
    }
  }
  else
  {
    Serial.println("Version check failed: " + String(httpCode));
    otaWebSetStatus("Version check failed");
  }

  http.end();
}
// ---------------- OTA PROCESS ----------------

void performOTA()
{
  Serial.println("Starting OTA Update...");
  displayShowOtaProgress(1);

  otaWebSetProgress(1);
  otaWebSetStatus("Updating...");

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(client, _firmwareUrl);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK)
  {
    int contentLength = http.getSize();
    Serial.println("Firmware Size: " + String(contentLength));

    if (contentLength <= 0)
    {
      Serial.println("Invalid firmware size!");
      otaWebSetStatus("Invalid size");
      http.end();
      return;
    }

    if (Update.begin(contentLength))
    {
      WiFiClient *stream = http.getStreamPtr();
      size_t written = 0;
      uint8_t buffer[128];

      while (http.connected() && written < contentLength)
      {
        otaWebHandle(); // 🔥 keep web alive

        size_t available = stream->available();

        if (available)
        {
          int len = stream->readBytes(buffer, min((int)available, 128));
          written += Update.write(buffer, len);

          int progress = (written * 100) / contentLength;

          if (progress < 1)
            progress = 1;
          if (progress > 100)
            progress = 100;

          displayShowOtaProgress(progress);
          otaWebSetProgress(progress);

          Serial.println("Progress: " + String(progress) + "%");
        }

        delay(1);
      }

      // ✅ FINAL SUCCESS BLOCK (FIXED)
      if (Update.end() && Update.isFinished())
      {
        displayShowOtaProgress(100);
        otaWebSetProgress(100);
        otaWebSetStatus("OTA Done - Restarting...");

        Serial.println("Update Successful!");
        Serial.println("Restarting in 3 seconds...");

        // 🔥 keep web alive so browser sees 100%
        unsigned long restartDelay = millis();
        while (millis() - restartDelay < 3000)
        {
          otaWebHandle();
          delay(10);
        }

        ESP.restart();
      }
      else
      {
        Serial.println("Update Failed!");
        otaWebSetStatus("Failed");
      }
    }
    else
    {
      Serial.println("Not enough space for OTA!");
      otaWebSetStatus("No space");
    }
  }
  else
  {
    Serial.println("Firmware download failed: " + String(httpCode));
    otaWebSetStatus("Download failed");
  }

  http.end();
}