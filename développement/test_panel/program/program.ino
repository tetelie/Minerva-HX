#include <SPI.h>
#include "buzzer.h"
#include "settings.h"
#include "screen.h"
#include "joystick.h"
#include "startup.h"
#include "menu.h"
#include "menu_sound.h"
#include "menu_joystick.h"
#include "menu_potentiometer.h"
#include "pin.h"

void setup() {
  Serial.begin(115200);     // set broadcast channel
  init_pin();               // set pin mode
  init_screen();            // setup screen
  loadSoundSettings();      // load settings from flash memory
  showLogoWithMelody();     // startup
  drawMenu(selectedOption); // display main menu
}

void loop() {
  int xVal = analogRead(xyzPins1[0]);   // read joystick x axis
  int yVal = analogRead(xyzPins1[1]);   // read joystick y axis
  int zVal = digitalRead(xyzPins1[2]);  // read joystick z axis



  // Joystick en haut
  if (yVal > 3000) {
    navigateMenu(-1);
    playMenuSound();
    drawMenu(selectedOption);
    delay(150);
  }
  // Joystick en bas
  else if (yVal < 1000) {
    navigateMenu(1);
    playMenuSound();
    drawMenu(selectedOption);
    delay(150);
  }
  // Bouton pressé
  if (zVal == LOW) {
    switch (selectedOption) {
      case 0:
        // Actions pour le menu "Mappings"
        break;
      case 1:
        joystickLiveView();
        break;
      case 2:
        potentiometerLiveView();
        break;
      case 3:
        soundSettingsMenu();
        break;
      case 4:
        // Actions pour "Color Settings"
        break;
      case 5:
        // Quitter l'application
        break;
    }
    delay(300);
  }
}
