#include <SPI.h>
#include "sound.h"
#include "settings.h"
#include "screen.h"
#include "startup.h"
#include "menu.h"
#include "menu_sound.h"
#include "menu_joystick.h"
#include "menu_slider.h"
#include "menu_theme.h"
#include "menu_mapping.h"
#include "pin.h"
#include "mapping.h"
#include "bridge.h"
#include "expender.h"


void setup() {
  Serial.begin(115200);     // set broadcast channel
  Serial.println("=== debut du setup===");
  init_pin();               // set pin mode
  init_screen();            // setup screen
  loadSettings();      // load settings from flash memory
  showLogoWithMelody();     // startup
  drawMenu(selectedOption); // display main menu
  initBridge();
  init_expender();
  init_map();
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  
  mcp.digitalWrite(5, HIGH);

  Serial.println("=== fin du setup===");


  //mcp.pinMode(6, INPUT_PULLUP);

/*. DEBUG START
  tft.fillScreen(ST77XX_BLACK);  // Remplir l'écran avec du noir
  tft.setTextColor(ST77XX_WHITE);  // Texte en blanc
  tft.setTextSize(2);  // Taille du texte
  tft.setCursor(10, 10);  // Position du curseur
  tft.print("Hello, ESP32!");
}
DEBUG STOP */
}


void loop() {
  /*Serial.println("test");
  delay(1000);
  //playSound(0, 100);
  int xVal = analogRead(JOYSTICK_1_X);   // read joystick x axis
  int yVal = analogRead(JOYSTICK_1_Y);   // read joystick y axis
  int zVal = digitalRead(JOYSTICK_1_Z);  // read joystick z axis

  Serial.println(xVal);
  Serial.println(yVal);
  Serial.println(zVal);

  //drawMenu(selectedOption);
  readMapSwitch();

  /*Serial.println("test send.");
  Serial2.println("test");

  delay(1000);*/
/**/

  readMapSwitch();


  mcp.digitalWrite(7, HIGH);


  int xVal = analogRead(JOYSTICK_1_X);   // read joystick x axis
  int yVal = analogRead(JOYSTICK_1_Y);   // read joystick y axis
  int zVal = digitalRead(JOYSTICK_1_Z);  // read joystick z axis

  //Serial.println(xVal);
  //Serial.println(yVal);
  //Serial.println(zVal);



  Serial.println("test");

  //Serial.println(mcp.digitalRead(6));

  int tes;

  tes = mcp.digitalRead(6);

  Serial.println(tes);

  if(!mapping){ // si mapping = 0
    if(updateMapping())
    {
      // disable
      disable_map();
      xVal = analogRead(JOYSTICK_1_X);   // read joystick x axis
      yVal = analogRead(JOYSTICK_1_Y);   // read joystick y axis
      zVal = digitalRead(JOYSTICK_1_Z);  // read joystick z axis
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
    playMenuSound();
    switch (selectedOption) {
      case 0:
        mappingSettingsMenu();
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
    delay(100);
  }
    mcp.digitalWrite(7, LOW);
    delay(100);

    Serial2.println("test");


}else{
  if(updateMapping())
  {
    start_map();
  }
  run_map();
}
}
