#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

extern uint16_t colors[];
extern int currentMainColor;
extern uint16_t getMainColor();
extern int colorsCount;
extern String colorOptions[];
