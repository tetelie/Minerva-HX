#include "menu.h"
#include "screen.h"

int selectedOption = 0;
String menuItems[] = {"Mappings", "Joystick", "Potentiometer","Sound Settings","Color Settings", "Quit"};
int menuSize = 4;

void drawMenu(int selected) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  int yStart = 60;
  int spacing = 40;
  int xLeft = 30; // marge gauche

  for (int i = 0; i < menuSize; i++) {
    int y = yStart + i * spacing;

    if (i == selected) {
      tft.fillRect(xLeft - 10, y - 5, 180, 30, ST77XX_BLUE);
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLUE);
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    }

    tft.setCursor(xLeft, y);
    tft.print(menuItems[i]);
  }
}
