#include "ota_web.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

// Internal variables
static int currentVersion = 0;
static int remoteVersion = 0;
static int otaProgress = 0;
static String otaStatus = "Idle";

// -------- HTML PAGE --------
String generateHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#111;color:#fff;}";
  html += ".box{margin:20px;padding:20px;border-radius:10px;background:#222;}";
  html += "</style></head><body>";

  html += "<h2>ESP32 OTA Dashboard</h2>";

  html += "<div class='box'>";
  html += "<p><b>Current Version:</b> " + String(currentVersion) + "</p>";
  html += "<p><b>Remote Version:</b> " + String(remoteVersion) + "</p>";
  html += "<p><b>Status:</b> " + otaStatus + "</p>";
  html += "<p><b>Progress:</b> " + String(otaProgress) + "%</p>";
  html += "</div>";

  html += "</body></html>";
  return html;
}

// -------- ROUTE --------
void handleRoot() {
  server.send(200, "text/html", generateHTML());
}

// -------- INIT --------
void otaWebInit() {

  server.on("/", handleRoot);

  server.begin();

  Serial.println("OTA Web Server Started");
  Serial.print("Open in browser: http://");
  Serial.println(WiFi.localIP());
}

// -------- LOOP --------
void otaWebHandle() {
  server.handleClient();
}

// -------- SETTERS --------
void otaWebSetCurrentVersion(int version) {
  currentVersion = version;
}

void otaWebSetRemoteVersion(int version) {
  remoteVersion = version;
}

void otaWebSetProgress(int progress) {
  otaProgress = progress;
}

void otaWebSetStatus(String status) {
  otaStatus = status;
}