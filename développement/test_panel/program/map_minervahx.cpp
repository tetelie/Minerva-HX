#include "map_minervahx.h"
#include <Arduino.h>
#include "screen.h"
#include "theme.h"


void minevervaHxMap_setup()
{

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(getMainColor());
  tft.setCursor(0, 30);
  tft.println("MinervaHx Mapping");

}

void minevervaHxMap_loop()
{
  Serial.print("MinervaHx map running.. \n");



}
