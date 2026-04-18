# NetZero Miniature V1

NetZero Miniature V1 is an ESP32-based automation and monitoring project built around four TM1637 7-segment displays, relay outputs, status LEDs, and a simple web-based OTA/version dashboard.

The firmware connects to Wi-Fi, shows the local IP address on the display at startup, fetches the current release version from GitHub, and then continues to run the switch-controlled relay/LED logic in the main loop.

## What the project does

- Connects the ESP32 to Wi-Fi using the credentials in `config.h`.
- Shows the device IP address on the 4-digit display modules during startup.
- Fetches the latest release version from `var.txt` stored in the GitHub repository.
- Displays the local firmware version and the latest published version on the first two displays.
- Controls relays, indicator LEDs, and carbon/emission visualization based on the physical switch inputs.
- Exposes a small OTA status web page on port 80.

## Hardware overview

- Board: ESP32
- Display: 4 x TM1637 7-segment display modules
- Outputs: relay channels, LED outputs, and two LED strips
- Inputs: five switch inputs for the operating modes

## File structure

- `netZero_miniature_V1.ino` - main setup and loop logic
- `config.h` - Wi-Fi, version, pin, and hardware constants
- `wifi_manager.cpp` / `wifi_manager.h` - Wi-Fi connection and IP display
- `display_manager.cpp` / `display_manager.h` - TM1637 display helpers
- `relay_manager.cpp` / `relay_manager.h` - relay initialization and control
- `led_manager.cpp` / `led_manager.h` - LED strip patterns and carbon visualization
- `ota.cpp` / `ota.h` - version fetch and OTA-related logic
- `ota_web.cpp` / `ota_web.h` - simple web dashboard for status and version values

## Startup flow

1. Serial begins at 115200 baud.
2. The display driver is initialized.
3. Wi-Fi connects.
4. The IP address is shown on the display.
5. The firmware reads the published version from GitHub `var.txt`.
6. The current firmware version and latest version are shown on the first two displays.
7. Relays, LEDs, and the OTA web server are initialized.

## Main loop flow

- Handles the OTA web server.
- Periodically checks the GitHub version file.
- Reads the switch inputs and updates relay/LED/carbon output logic.
- Updates the four display modules with the counter values.

## Display behavior

- Startup IP display: the local IP is shown after Wi-Fi connects.
- Version display: current version is shown on display 1 and latest version on display 2.
- Counter display: the main loop later updates all four displays with the runtime counters.

If you want the version values to stay visible longer, increase the startup delay after the version check or avoid calling `displayUpdate()` immediately in the loop.

## Configuration

All project configuration lives in `config.h`.

Important values:

- `WIFI_SSID` and `WIFI_PASSWORD` - Wi-Fi credentials
- `CURRENT_VERSION` - local firmware version embedded in the build
- `VERSION_URL` - GitHub raw URL for `var.txt`
- `FIRMWARE_URL` - GitHub raw URL for `firmware.bin`
- `OTA_CHECK_INTERVAL` - time between version checks
- Pin assignments for displays, relays, switches, LEDs, and LED strips

## Building and uploading

1. Open the project in Arduino IDE or PlatformIO.
2. Select the correct ESP32 board.
3. Verify that the required libraries are installed:
   - `WiFi`
   - `HTTPClient`
   - `Update`
   - `WebServer`
   - `FastLED`
   - `TM1637Display`
4. Build the sketch.
5. Upload it to the ESP32.

## Operational notes

- The project depends on GitHub raw URLs being reachable from the ESP32 network.
- If Wi-Fi does not connect, startup version checks and the web dashboard will not work.
- `var.txt` should contain only the version number, for example `2`.
- Keep `CURRENT_VERSION` in code aligned with the firmware release you want to ship.

## Troubleshooting

- No IP on the display: verify Wi-Fi credentials and board wiring.
- Wrong version displayed: confirm that `var.txt` contains a plain integer and that `VERSION_URL` points to the correct branch.
- Web dashboard not reachable: check the device IP and make sure the ESP32 is connected to Wi-Fi.
- Displays not responding: verify the TM1637 pin mapping in `config.h`.
