#include <SPI.h>
#include "buzzer.h"
#include "settings.h"
#include "screen.h"
#include "startup.h"
#include "menu.h"
#include "menu_sound.h"
#include "menu_joystick.h"
#include "menu_potentiometer.h"
#include "menu_theme.h"
#include "pin.h"
#include "mapping.h"


void setup() {
  Serial.begin(115200);     // set broadcast channel
  init_pin();               // set pin mode
  init_screen();            // setup screen
  loadSettings();      // load settings from flash memory
  showLogoWithMelody();     // startup
  drawMenu(selectedOption); // display main menu
  init_map();
}



void loop() {
  int xVal = analogRead(JOYSTICK_1_X);   // read joystick x axis
  int yVal = analogRead(JOYSTICK_1_Y);   // read joystick y axis
  int zVal = digitalRead(JOYSTICK_1_Z);  // read joystick z axis

  readMapSwitch();

  if(!mapping){ // si mapping = 0
    if(updateMapping())
    {
      drawMenu(selectedOption);
    }

  //Serial.print(mapping);

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
        themeSettingsMenu();
        break;
      case 5:
        // Quitter l'application
        break;
    }
    delay(300);
  }

}else{
  if(updateMapping())
  {
    start_map();
  }
}
}
