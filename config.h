#ifndef CONFIG_H
#define CONFIG_H

// -------- WiFi --------
#define WIFI_SSID "IIIT-Guest"
#define WIFI_PASSWORD "f6s68VHJ89mC"

// -------- OTA --------
#define CURRENT_VERSION 2
#define VERSION_URL "https://raw.githubusercontent.com/smartcityresearch/miniature-code/main/var.txt"
#define FIRMWARE_URL "https://raw.githubusercontent.com/smartcityresearch/miniature-code/main/firmware.bin"
#define OTA_CHECK_INTERVAL 60000

// -------- TM1637 --------
#define CLK 22
#define DIO1 23
#define DIO2 21
#define DIO3 19
#define DIO4 18

// -------- SWITCHES --------
#define SOLAR_SW 32
#define RAIN_SW 33
#define STP_SW 25
#define GRID_SW 26
#define BOREWELL_SW 27

#define SOLAR_LED 17
#define GRID_LED 12

// -------- RELAYS --------
// r1=16,r2=4,r3=2,r4=15
#define RELAY_RAIN 15
#define RELAY_STP 2
#define RELAY_BOREWELL 4
#define RELAY_EXTRA 16 // future purpose

// -------- LED STRIP --------
#define EMISSION_PIN 13
#define REDUCTION_PIN 14
#define NUM_LEDS 13

#endif