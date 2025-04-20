#include "settings.h"
#include "buzzer.h"
#include <Arduino.h>
#include <Preferences.h>


Preferences preferences;  // <- définition réelle de la variable globale


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
