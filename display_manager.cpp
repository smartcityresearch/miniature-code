#include "display_manager.h"
#include <TM1637Display.h>
#include "config.h"

TM1637Display disp1(CLK, DIO1);
TM1637Display disp2(CLK, DIO2);
TM1637Display disp3(CLK, DIO3);
TM1637Display disp4(CLK, DIO4);

void displayInit()
{
  disp1.setBrightness(7);
  disp2.setBrightness(7);
  disp3.setBrightness(7);
  disp4.setBrightness(7);

  disp1.clear();
  disp2.clear();
  disp3.clear();
  disp4.clear();
}

void displayUpdate(int c1, int c2, int c3, int c4)
{
  disp1.showNumberDec(c1, false);
  disp2.showNumberDec(c2, false);
  disp3.showNumberDec(c3, false);
  disp4.showNumberDec(c4, false);
}

void displayShowOtaProgress(int progress)
{
  disp4.showNumberDec(progress, false);
}

void displayShowIP(String ip)
{

  int parts[4] = {0};
  int index = 0;

  // Split IP by '.'
  for (int i = 0; i < ip.length(); i++)
  {
    if (ip[i] == '.')
    {
      index++;
    }
    else
    {
      parts[index] = parts[index] * 10 + (ip[i] - '0');
    }
  }

  // Display each part
  disp1.showNumberDec(parts[0], false);
  disp2.showNumberDec(parts[1], false);
  disp3.showNumberDec(parts[2], false);
  disp4.showNumberDec(parts[3], false);
}

void displayShowVersions(int currentVersion, int latestVersion)
{
  disp1.showNumberDec(currentVersion, false);
  disp2.showNumberDec(latestVersion, false);

  disp3.clear();
  disp4.clear();
}