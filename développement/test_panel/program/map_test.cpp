#include "map_test.h"
#include <Arduino.h>
#include "screen.h"
#include "theme.h"


void testMap_setup()
{

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(getMainColor());
  tft.setCursor(0, 10);
  tft.println("Test Map");

}

void testMap_loop()
{

  static int lastX = -1;


  static int lastXVal = -1;

  int xVal = analogRead(15);

  int xBarLength = map(xVal, 0, 4095, 0, 160);

    // Mise à jour intelligente de la jauge X
    if (xBarLength != lastX) {
      if (xBarLength > lastX) {
        tft.fillRect(40 + lastX, 50, xBarLength - lastX, 10, getMainColor());
      } else {
        tft.fillRect(40 + xBarLength, 50, lastX - xBarLength, 10, ST77XX_BLACK);
      }
      lastX = xBarLength;
    }

    // Affichage intelligent des valeurs X
    if (xVal != lastXVal) {
      tft.fillRect(210, 50, 50, 20, ST77XX_BLACK);
      tft.setCursor(210, 50);
      tft.print(xVal);
      lastXVal = xVal;
    }

    delay(50);

}
