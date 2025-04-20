#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

extern Adafruit_ST7789 tft;

void init_screen();
