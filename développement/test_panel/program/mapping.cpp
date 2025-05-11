#include "mapping.h"
#include <Arduino.h>
#include "screen.h"
#include "theme.h"
#include "sound.h"
#include "map_minervahx.h"
#include "map_test.h"
#include "pin.h"
#include "expender.h"

int map_buffer = 0;
int mapping = 0;

int activeMapIndex = 1;

String mappingOptions[] = {"None", "MinervaHx", "Test"};
int mappingCount = 3;


typedef void (*MapFunction)();

MapFunction maps_loop[] = {
  nullptr,
  minevervaHxMap_loop,
  testMap_loop
};

MapFunction maps_setup[] = {
  nullptr,
  minevervaHxMap_setup,
  testMap_setup
};

MapFunction maps_disable[] = {
  nullptr,
  nullptr,
  testMap_disable
};

void init_map(){
  readMapSwitch();
  map_buffer = mapping;
  if(mapping) start_map();
}
void readMapSwitch()
{
  mapping = mcp.digitalRead(MAPPING_SWITCH);
}

int updateMapping(){
  if(mapping != map_buffer)
  {
    // changement d'état
    map_buffer = mapping;
    if(!mapping) playMenuSound();
    return 1;
  }
  return 0;
}

void run_map()
{
  maps_loop[activeMapIndex]();
}

void disable_map()
{
  maps_disable[activeMapIndex]();
}

void start_map() {
  int xOffset = 50;

  tft.fillScreen(ST77XX_BLACK);

  uint16_t boxColor = getMainColor();
  uint16_t textColor = ST77XX_WHITE;
  int boxX = xOffset;
  int boxY = 60;
  int boxW = 240 - 20;  // Garde des marges égales
  int boxH = 100;

  // Cadre arrondi
  tft.drawRoundRect(boxX, boxY, boxW, boxH, 15, boxColor);
  tft.drawRoundRect(boxX + 2, boxY + 2, boxW - 4, boxH - 4, 13, boxColor);

  // Titre
  tft.setTextSize(2);
  tft.setTextColor(textColor);
  tft.setCursor(boxX + 20, boxY + 20);  // Décalage horizontal depuis la gauche du cadre
  tft.println("Starting Map");

  // Nom de la map
  tft.setTextSize(1);
  tft.setCursor(boxX + 20, boxY + 60);
  tft.print(mappingOptions[activeMapIndex]);

  // Petites bulles animées 
  for (int i = 0; i < 3; i++) {
    if(soundEnabled) playSound(i, 100);
    tft.fillCircle(boxX + boxW - 40 + i * 8, boxY + boxH - 15, 3, boxColor);
    delay(600);
  }

  delay(500);
  tft.fillScreen(ST77XX_BLACK);

  maps_setup[activeMapIndex]();
}
