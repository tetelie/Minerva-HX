#include "mapping.h"
#include <Arduino.h>
#include "screen.h"
#include "theme.h"
#include "buzzer.h"

int map_buffer = 0;
int mapping = 0;

void init_map(){
  readMapSwitch();
  map_buffer = mapping;
  if(mapping) start_map();
}
void readMapSwitch()
{
  mapping = digitalRead(32);
}

int updateMapping(){
  if(mapping != map_buffer)
  {
    // changement d'état
    playMenuSound();
    map_buffer = mapping;
    return 1;
  }
  return 0;
}

void start_map()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(getMainColor());
  tft.setCursor(0, 30);
  tft.println("Start Mapping..");
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}
