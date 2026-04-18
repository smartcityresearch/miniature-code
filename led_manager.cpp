#include "led_manager.h"
#include <FastLED.h>
#include "config.h"

CRGB emissionLEDs[NUM_LEDS];
CRGB reductionLEDs[NUM_LEDS];
uint8_t hueOffset = 0;

void ledInit() {
  FastLED.addLeds<WS2812B, EMISSION_PIN, GRB>(emissionLEDs, NUM_LEDS);
  FastLED.addLeds<WS2812B, REDUCTION_PIN, GRB>(reductionLEDs, NUM_LEDS);
  FastLED.setBrightness(120);
}

void ledRunGradient(int mode) {

  for(int i = 0; i < NUM_LEDS; i++) {

    switch(mode) {

      case 1:
        emissionLEDs[i]  = CHSV(0 + i*3, 255, 255);
        reductionLEDs[i] = CHSV(20 + i*3, 255, 255);
        break;

      case 2:
        emissionLEDs[i]  = CHSV(96 + i*2, 255, 255);
        reductionLEDs[i] = CHSV(64 + i*2, 255, 255);
        break;

      case 3:
        emissionLEDs[i]  = CHSV(160 + i*2, 255, 255);
        reductionLEDs[i] = CHSV(140 + i*2, 255, 255);
        break;

      case 4:
        emissionLEDs[i]  = CHSV(200 + i*2, 255, 255);
        reductionLEDs[i] = CHSV(220 + i*2, 255, 255);
        break;

      case 5:
        emissionLEDs[i]  = CHSV(hueOffset + i*5, 255, 255);
        reductionLEDs[i] = CHSV(hueOffset + 128 + i*5, 255, 255);
        break;
    }
  }

  if(mode == 5) hueOffset++;

  FastLED.show();
}


void setCarbon(int emissionPercent, int reductionPercent)
{
  int emissionLEDCount = (NUM_LEDS * emissionPercent) / 100;
  int reductionLEDCount = (NUM_LEDS * reductionPercent) / 100;

  // -------- EMISSION (RED GRADIENT) --------
  for(int i = 0; i < NUM_LEDS; i++)
  {
    if(i < emissionLEDCount)
    {
      // brightness from 40 → 255
      uint8_t brightness = map(i, 0, emissionLEDCount - 1, 40, 255);
      emissionLEDs[i] = CRGB(brightness, 0, 0);
    }
    else
    {
      emissionLEDs[i] = CRGB::Black;
    }
  }

  // -------- REDUCTION (GREEN GRADIENT) --------
  for(int i = 0; i < NUM_LEDS; i++)
  {
    if(i < reductionLEDCount)
    {
      uint8_t brightness = map(i, 0, reductionLEDCount - 1, 40, 255);
      reductionLEDs[i] = CRGB(0, brightness, 0);
    }
    else
    {
      reductionLEDs[i] = CRGB::Black;
    }
  }

  FastLED.show();
}