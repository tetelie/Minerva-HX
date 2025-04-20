#include "theme.h"

int currentMainColor = 0;

uint16_t colors[] = {ST77XX_BLUE, ST77XX_RED, ST77XX_GREEN, ST77XX_CYAN, ST77XX_YELLOW, ST77XX_MAGENTA,ST77XX_ORANGE};

extern uint16_t getMainColor()
{
  return colors[currentMainColor];
}

int colorsCount = 7;

String colorOptions[] = {"Blue", "Red", "Green", "Cyan", "Yellow", "Magenta", "Orange"};  // Liste des options
