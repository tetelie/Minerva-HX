#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "logo.h"
#include <Preferences.h>  // Bibliothèque pour la persistance dans la mémoire Flash

const int buzzerPin = 13;
int xyzPins1[] = {14, 12, 27}; // x, y, bouton (z)

// Notes musicales
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int selectedOption = 0;
String menuItems[] = {"Mappings", "Joystick", "Potentiometer","Sound Settings","Color Settings", "Quit"};
const int menuSize = 4;

// Variables pour le son
bool soundEnabled = true;
int currentSound = 0;  // 0 -> Son A (C5), 1 -> Son B (D5), 2 -> Son C (E5), 3 -> Désactiver

// Objet pour la persistance dans la mémoire Flash
Preferences preferences;

// === Fonctions ===

void playMenuSound() {
  if (!soundEnabled) return;  // Si le son est désactivé, on ne joue rien
  
  int soundNote = NOTE_C5;
  switch (currentSound) {
    case 0: soundNote = NOTE_C5; break;
    case 1: soundNote = NOTE_D5; break;
    case 2: soundNote = NOTE_E5; break;
    case 3: return;  // Pas de son si "désactiver"
  }

  tone(buzzerPin, soundNote, 100);  // Jouer la note pendant 100ms
  delay(150);  // Pause pour que le son soit audible
  noTone(buzzerPin);  // Arrêter le son
}

void showLogoWithMelody() {
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(96, 56, logo, 128, 128);

  // Notes et durées correspondantes
  int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5};
  int durations[] = {200, 200, 200, 200, 300, 300};

  unsigned long startTime = millis();
  int noteIndex = 0;
  bool notePlaying = false;
  unsigned long noteStartTime = 0;

  while (millis() - startTime < 3000) {
    if (!notePlaying && noteIndex < 6) {
      tone(buzzerPin, melody[noteIndex], durations[noteIndex]);
      noteStartTime = millis();
      notePlaying = true;
    }

    if (notePlaying && millis() - noteStartTime > durations[noteIndex] * 1.3) {
      noTone(buzzerPin);
      noteIndex++;
      notePlaying = false;
    }
  }
  noTone(buzzerPin); // arrêt de sécurité
}

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

void showSoundMenu(String* soundOptions, int soundMenuSize, int yStart, int spacing, int xLeft)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int i = 0; i < soundMenuSize; i++) {
    int y = yStart + i * spacing;

    if (i == currentSound) {
      tft.fillRect(xLeft - 10, y - 5, 180, 30, ST77XX_BLUE);
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLUE);
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

  bool inSoundMenu = true;
  while (inSoundMenu) {
    int xVal = analogRead(xyzPins1[0]);
    int yVal = analogRead(xyzPins1[1]);
    int zVal = digitalRead(xyzPins1[2]);

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
      saveSoundSettings();  // Sauvegarder les paramètres dans la mémoire Flash
      inSoundMenu = false;  // Quitter le menu des sons
      drawMenu(selectedOption);  // Retour au menu principal
    }

    delay(50);
  }
}

void saveSoundSettings() {
  preferences.begin("soundSettings", false);  // Ouvrir l'espace de stockage "soundSettings"
  preferences.putBool("soundEnabled", soundEnabled);  // Sauvegarder l'état du son
  preferences.putInt("currentSound", currentSound);  // Sauvegarder l'option de son
  preferences.end();  // Fermer l'espace de stockage
}

void loadSoundSettings() {
  preferences.begin("soundSettings", true);  // Ouvrir en mode lecture l'espace de stockage "soundSettings"
  soundEnabled = preferences.getBool("soundEnabled", true);  // Lire l'état du son, valeur par défaut true
  currentSound = preferences.getInt("currentSound", 0);  // Lire l'option de son, valeur par défaut 0
  preferences.end();  // Fermer l'espace de stockage
}

void joystickLiveView() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(20, 10);
  tft.println("Joystick Live");

  // Jauge X - barre horizontale
  tft.setCursor(10, 50);
  tft.print("X:");
  tft.drawRect(40, 50, 160, 10, ST77XX_WHITE);  // Jauge X horizontale

  // Jauge Y - barre horizontale
  tft.setCursor(10, 80);
  tft.print("Y:");
  tft.drawRect(40, 80, 160, 10, ST77XX_WHITE);  // Jauge Y horizontale

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
    int xVal = analogRead(xyzPins1[0]);
    int yVal = analogRead(xyzPins1[1]);
    int zVal = digitalRead(xyzPins1[2]);

    int xBarLength = map(xVal, 0, 4095, 0, 160);  // Taille de la barre X
    int yBarLength = map(yVal, 0, 4095, 0, 160);  // Taille de la barre Y

    // Mise à jour de la jauge X
    if (xBarLength != lastX) {
      tft.fillRect(40, 50, 160, 10, ST77XX_BLACK);  // Efface l'ancienne jauge
      tft.fillRect(40, 50, xBarLength, 10, ST77XX_RED);  // Nouvelle jauge
      lastX = xBarLength;
    }

    // Mise à jour de la jauge Y
    if (yBarLength != lastY) {
      tft.fillRect(40, 80, 160, 10, ST77XX_BLACK);  // Efface l'ancienne jauge
      tft.fillRect(40, 80, yBarLength, 10, ST77XX_GREEN);  // Nouvelle jauge
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

void potentiometerLiveView() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(20, 10);
  tft.println("Potentiometer Live");

  // Jauge X - barre horizontale
  tft.setCursor(10, 50);
  tft.print("LP");
  tft.drawRect(40, 50, 160, 10, ST77XX_WHITE);  // Jauge X horizontale

  // Jauge Y - barre horizontale
  tft.setCursor(10, 80);
  tft.print("RP");
  tft.drawRect(40, 80, 160, 10, ST77XX_WHITE);  // Jauge Y horizontale

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
    int xVal = analogRead(15);
    int yVal = 4095-analogRead(0);
    int zVal = digitalRead(xyzPins1[2]);

    int xBarLength = map(xVal, 0, 4095, 0, 160);  // Taille de la barre X
    int yBarLength = map(yVal, 0, 4095, 0, 160);  // Taille de la barre Y

    // Mise à jour de la jauge X
    if (xBarLength != lastX) {
      tft.fillRect(40, 50, 160, 10, ST77XX_BLACK);  // Efface l'ancienne jauge
      tft.fillRect(40, 50, xBarLength, 10, ST77XX_RED);  // Nouvelle jauge
      lastX = xBarLength;
    }

    // Mise à jour de la jauge Y
    if (yBarLength != lastY) {
      tft.fillRect(40, 80, 160, 10, ST77XX_BLACK);  // Efface l'ancienne jauge
      tft.fillRect(40, 80, yBarLength, 10, ST77XX_GREEN);  // Nouvelle jauge
      lastY = yBarLength;
    }

    // Affichage de l'état du bouton
    if (zVal != lastZ) {
      tft.fillRect(70, 180, 160, 20, ST77XX_BLACK);  // Effacer la zone du bouton
      tft.setCursor(70, 180);
      tft.setTextColor(zVal == LOW ? ST77XX_GREEN : ST77XX_WHITE);
      tft.print("exit (press 1s)");
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

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  pinMode(15, INPUT);
  pinMode(0, INPUT);  
  pinMode(32, INPUT_PULLUP);
  pinMode(xyzPins1[2], INPUT_PULLUP);
  tft.init(240, 320);
  tft.setRotation(1);

  loadSoundSettings();  // Charger les paramètres sonores depuis la mémoire Flash

  showLogoWithMelody();
  drawMenu(selectedOption);
}

void loop() {
  Serial.println(digitalRead(32));
  delay(200);

  int xVal = analogRead(xyzPins1[0]);
  int yVal = analogRead(xyzPins1[1]);
  int zVal = digitalRead(xyzPins1[2]);



  // Joystick en haut
  if (yVal > 3000) {
    selectedOption--;
    if (selectedOption < 0) selectedOption = menuSize - 1;
    playMenuSound();
    drawMenu(selectedOption);
    delay(150);
  }
  // Joystick en bas
  else if (yVal < 1000) {
    selectedOption++;
    if (selectedOption >= menuSize) selectedOption = 0;
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
    delay(500);
  }
}
