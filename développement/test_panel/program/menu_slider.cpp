#include "menu_slider.h"
#include "screen.h"
#include "pin.h"
#include "sound.h"
#include "menu.h"
#include "theme.h"

void potentiometerLiveView() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(20, 10);
  tft.println("Potentiometer Live");

  // Jauge X - barre horizontale
  tft.setCursor(10, 50);
  tft.print("LP");
  //tft.drawRect(40, 50, 160, 10, ST77XX_WHITE);  // Jauge X horizontale

  // Jauge Y - barre horizontale
  tft.setCursor(10, 80);
  tft.print("RP");
  //tft.drawRect(40, 80, 160, 10, ST77XX_WHITE);  // Jauge Y horizontale

  // Variables pour afficher les valeurs
  int lastX = -1;
  int lastY = -1;
  int lastZ = -1;
  unsigned long buttonPressStart = 0;
  bool buttonHeld = false;
  bool inJoystickView = true;

  int lastXVal = -1;
  int lastYVal = -1;

  while (inJoystickView) {
    int xVal = analogRead(LEFT_SLIDER);
    int yVal = 4095 - analogRead(0);
    int zVal = digitalRead(JOYSTICK_1_Z);

    int xBarLength = map(xVal, 0, 4095, 0, 160);
    int yBarLength = map(yVal, 0, 4095, 0, 160);

    // Mise à jour intelligente de la jauge X
    if (xBarLength != lastX) {
      if (xBarLength > lastX) {
        tft.fillRect(40 + lastX, 50, xBarLength - lastX, 10, getMainColor());
      } else {
        tft.fillRect(40 + xBarLength, 50, lastX - xBarLength, 10, ST77XX_BLACK);
      }
      lastX = xBarLength;
    }

    // Mise à jour intelligente de la jauge Y
    if (yBarLength != lastY) {
      if (yBarLength > lastY) {
        tft.fillRect(40 + lastY, 80, yBarLength - lastY, 10, getMainColor());
      } else {
        tft.fillRect(40 + yBarLength, 80, lastY - yBarLength, 10, ST77XX_BLACK);
      }
      lastY = yBarLength;
    }

    // Affichage de l'état du bouton
    if (zVal != lastZ) {
      tft.fillRect(70, 180, 160, 20, ST77XX_BLACK);
      tft.setCursor(70, 180);
      tft.setTextColor(zVal == LOW ? ST77XX_GREEN : ST77XX_WHITE);
      tft.print("exit (press 1s)");
      lastZ = zVal;
    }

    // Affichage intelligent des valeurs X
    if (xVal != lastXVal) {
      tft.fillRect(210, 50, 50, 20, ST77XX_BLACK);
      tft.setCursor(210, 50);
      tft.print(xVal);
      lastXVal = xVal;
    }

    // Affichage intelligent des valeurs Y
    if (yVal != lastYVal) {
      tft.fillRect(210, 80, 50, 20, ST77XX_BLACK);
      tft.setCursor(210, 80);
      tft.print(yVal);
      lastYVal = yVal;
    }

    // Détection d'appui long
    if (zVal == LOW) {
      if (!buttonHeld) {
        buttonPressStart = millis();
        buttonHeld = true;
      } else if (millis() - buttonPressStart >= 1000) {
        inJoystickView = false;
        playMenuSound();
        delay(500);
      }
    } else {
      buttonHeld = false;
    }

    delay(50);
  }

  drawMenu(selectedOption);
}
