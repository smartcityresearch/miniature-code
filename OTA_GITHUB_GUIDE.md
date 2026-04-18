# GitHub OTA and Version Management Guide

This document explains how version checking and OTA release management are intended to work for NetZero Miniature V1 using GitHub-hosted files.

## Overview

The firmware reads a version number from:

`https://raw.githubusercontent.com/smartcityresearch/miniature-code/main/var.txt`

That file acts as the release marker. The ESP32 uses it to compare:

- `CURRENT_VERSION` in `config.h`
- the latest published version in `var.txt`

The firmware also points to the firmware binary hosted on GitHub:

`https://raw.githubusercontent.com/smartcityresearch/miniature-code/main/firmware.bin`

## Versioning model

Use a simple integer version scheme.

Example:

- First release: `1`
- Next release: `2`
- Next release: `3`

Rules:

- Increase the version number every time you publish a new firmware build.
- Keep `CURRENT_VERSION` in the code equal to the version built into that firmware.
- Keep `var.txt` equal to the latest available public version.

## Recommended GitHub files

Store these files in the repository root or in the exact paths referenced by `config.h`:

- `var.txt` - contains only the latest version number
- `firmware.bin` - compiled firmware binary

Keep `var.txt` as plain text with no extra words, symbols, or line breaks if possible.

Valid `var.txt` contents:

```text
2
```

Invalid `var.txt` contents:

```text
version 2
```

```text
2.0
```

```text
latest=2
```

## How OTA checking works

At startup, the firmware:

1. Connects to Wi-Fi.
2. Shows the local IP address on the display.
3. Fetches `var.txt` from GitHub.
4. Reads the version number.
5. Compares it with `CURRENT_VERSION`.
6. Displays the current version and latest version on the first two display modules.

When the firmware sees that the remote version is newer than the local version, it can report that an update is available.

## Typical release workflow

Use this sequence every time you publish a new firmware version.

### 1. Build the new firmware

- Increment `CURRENT_VERSION` in `config.h`.
- Rebuild the ESP32 sketch.
- Export or generate a fresh `firmware.bin`.

### 2. Upload the firmware binary to GitHub

- Replace the repository’s `firmware.bin` with the new build output.
- Commit and push the change.

### 3. Update `var.txt`

- Change `var.txt` to the new version number.
- Commit and push that file.

The simplest order is:

1. Upload the new `firmware.bin`.
2. Update `var.txt` to the same version number.

That ensures devices only see the new version number after the firmware file is already available.

## Safe update strategy

Always publish the binary before increasing the version marker.

Why this matters:

- If `var.txt` is updated first, devices may think an update exists before the binary is actually available.
- If the binary is published first, devices can safely discover the update after the release is ready.

## Example release procedure

Suppose the current release is version `2` and you want to publish version `3`.

1. Change `CURRENT_VERSION` in `config.h` to `3`.
2. Build the firmware.
3. Replace `firmware.bin` in GitHub with the new binary.
4. Update `var.txt` to:

```text
3
```

5. Commit and push both files.
6. Devices will read version `3` from GitHub and compare it against their local version.

## Manual version check on the device

The device can read the GitHub version file without performing a flash update.

This is useful when you want to:

- confirm connectivity
- verify the latest published version
- show the current and latest versions on the displays

## If you later want full OTA flashing

If you decide to restore actual OTA flashing, the usual flow is:

1. Read `var.txt`.
2. Compare with `CURRENT_VERSION`.
3. If a newer version exists, download `firmware.bin`.
4. Write the binary using the ESP32 update API.
5. Restart the device after flashing succeeds.

Keep the version check and the binary download as separate steps. That makes release management easier and reduces the chance of flashing the wrong build.

## Troubleshooting version issues

- Device always shows the old version: verify that `CURRENT_VERSION` was incremented and that the new firmware was actually uploaded.
- Device says an update is available but nothing changes: verify that `firmware.bin` matches the version number in `var.txt`.
- GitHub fetch fails: confirm the raw URL is correct and the ESP32 has internet access.
- Version parses incorrectly: make sure `var.txt` contains only a plain integer.
