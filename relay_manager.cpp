#include "relay_manager.h"
#include "config.h"
#include <Arduino.h>
int relays[] = {RELAY_RAIN, RELAY_STP, RELAY_BOREWELL, RELAY_EXTRA};

void relayInit()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
  }
}

void relayControl(int r1, int r2, int r3, int r4)
{
  digitalWrite(relays[0], r1 ? LOW : HIGH);
  digitalWrite(relays[1], r2 ? LOW : HIGH);
  digitalWrite(relays[2], r3 ? LOW : HIGH);
  digitalWrite(relays[3], r4 ? LOW : HIGH);
}

