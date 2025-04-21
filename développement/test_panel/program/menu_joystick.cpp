#include "menu_joystick.h"
#include "screen.h"
#include "pin.h"
#include "sound.h"
#include "menu.h"
#include "theme.h"

void joystickLiveView() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(20, 10);
  tft.println("Joystick Live");

  // Jauge X - barre horizontale
  tft.setCursor(10, 50);
  tft.print("X:");
  //tft.drawRect(40, 50, 160, 10, ST77XX_WHITE);  // Jauge X horizontale

  // Jauge Y - barre horizontale
  tft.setCursor(10, 80);
  tft.print("Y:");
  //tft.drawRect(40, 80, 160, 10, ST77XX_WHITE);  // Jauge Y horizontale

  // Variables pour afficher les valeurs
  int lastX = -1;
  int lastY = -1;
  int lastZ = -1;
  unsigned long buttonPressStart = 0;
  bool buttonHeld = false;
  bool inJoystickView = true;  // Variable pour éviter de retourner immédiatement

  // Variables pour gérer l'affichage des valeurs
  int lastXVal = -1;
  int lastYVal = -1;

  while (inJoystickView) {
    int xVal = analogRead(JOYSTICK_1_X);
    int yVal = analogRead(JOYSTICK_1_Y);
    int zVal = digitalRead(JOYSTICK_1_Z);

    int xBarLength = map(xVal, 0, 4095, 0, 160);  // Taille de la barre X
    int yBarLength = map(yVal, 0, 4095, 0, 160);  // Taille de la barre Y

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
      tft.fillRect(70, 180, 160, 20, ST77XX_BLACK);  // Effacer la zone du bouton
      tft.setCursor(70, 180);
      tft.setTextColor(zVal == LOW ? ST77XX_GREEN : ST77XX_WHITE);
      tft.print("button: ");
      tft.print(zVal == LOW ? "push" : "released");
      lastZ = zVal;
    }

    // Effacer les anciennes valeurs X et Y
    if (xVal != lastXVal) {
      tft.fillRect(210, 50, 50, 20, ST77XX_BLACK);  // Efface l'ancienne valeur X
      tft.setCursor(210, 50);
      tft.print(xVal);  // Affichage de la nouvelle valeur X
      lastXVal = xVal;
    }

    if (yVal != lastYVal) {
      tft.fillRect(210, 80, 50, 20, ST77XX_BLACK);  // Efface l'ancienne valeur Y
      tft.setCursor(210, 80);
      tft.print(yVal);  // Affichage de la nouvelle valeur Y
      lastYVal = yVal;
    }

    // Détection d'appui long pour quitter
    if (zVal == LOW) {
      if (!buttonHeld) {
        buttonPressStart = millis();
        buttonHeld = true;
      } else if (millis() - buttonPressStart >= 1000) {  // Appui long (1 seconde)
        inJoystickView = false;  // Quitter la vue joystick
        playMenuSound();  // Son lors du changement d'option
        delay(500);
      }
    } else {
      buttonHeld = false;  // Réinitialisation si on relâche le bouton
    }

    delay(50);
  }

  drawMenu(selectedOption);  // Retour au menu après avoir quitté
}
