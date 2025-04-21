#include "menu_sound.h"
#include "screen.h"
#include "sound.h"
#include "pin.h"
#include "settings.h"
#include "menu.h"
#include "theme.h"


void showSoundMenu(String* soundOptions, int soundMenuSize, int yStart, int spacing, int xLeft)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int i = 0; i < soundMenuSize; i++) {
    int y = yStart + i * spacing;

    if (i == currentSound) {
      tft.fillRect(xLeft - 10, y - 5, 180, 30, getMainColor());
      tft.setTextColor(ST77XX_WHITE, getMainColor());
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    }

    tft.setCursor(xLeft, y);
    tft.print(soundOptions[i]);
  }
}

void soundSettingsMenu() {
  int soundMenuSize = 4;
  String soundOptions[] = {"sound A (C5)", "sound B (D5)", "sound C (E5)", "disable"};

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  int yStart = 60;
  int spacing = 40;
  int xLeft = 30;

  // Affichage du sous-menu des sons
  showSoundMenu(soundOptions,soundMenuSize,yStart,spacing,xLeft);
  delay(150);
  bool inSoundMenu = true;
  while (inSoundMenu) {
    int xVal = analogRead(JOYSTICK_1_X);
    int yVal = analogRead(JOYSTICK_1_Y);
    int zVal = digitalRead(JOYSTICK_1_Z);

    // Joystick vers le haut
    if (yVal > 3000) {
      currentSound--;
      if (currentSound < 0) currentSound = soundMenuSize - 1;
      playMenuSound();
      showSoundMenu(soundOptions,soundMenuSize,yStart,spacing,xLeft);
      delay(150);
    }
    // Joystick vers le bas
    else if (yVal < 1000) {
      currentSound++;
      if (currentSound >= soundMenuSize) currentSound = 0;
      playMenuSound();
      showSoundMenu(soundOptions,soundMenuSize,yStart,spacing,xLeft);
      delay(150);
    }

    // Bouton pressé
    if (zVal == LOW) {
      tft.fillScreen(ST77XX_BLACK);


      // Sauvegarder la sélection de son
      if (currentSound == 3) {
        soundEnabled = false;  // Désactiver le son
      } else {
        soundEnabled = true;  // Activer le son
      }
      playMenuSound();  // Son lors du changement d'option
      saveSettings();  // Sauvegarder les paramètres dans la mémoire Flash
      inSoundMenu = false;  // Quitter le menu des sons
      drawMenu(selectedOption);  // Retour au menu principal
    }

    delay(50);
  }
}
