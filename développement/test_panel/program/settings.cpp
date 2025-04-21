#include "settings.h"
#include "sound.h"
#include <Arduino.h>
#include <Preferences.h>
#include "theme.h"
#include "mapping.h"

Preferences preferences;  // <- définition réelle de la variable globale

void saveThemeSettings() {
  preferences.begin("themeSettings", false);  // Ouvrir l'espace de stockage "soundSettings"
  preferences.putInt("currentTheme", currentMainColor);  // Sauvegarder l'option de son
  preferences.end();  // Fermer l'espace de stockage
}

void loadThemeSettings() {
  preferences.begin("themeSettings", true);  // Ouvrir en mode lecture l'espace de stockage "soundSettings"
  currentMainColor = preferences.getInt("currentTheme", 0);  // Lire l'option de son, valeur par défaut 0
  preferences.end();  // Fermer l'espace de stockage
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

void saveMapSettings() {
  preferences.begin("mapSettings", false);  // Ouvrir l'espace de stockage "soundSettings"
  preferences.putInt("activeMapIndex", activeMapIndex);  // Sauvegarder l'option de son
  preferences.end();  // Fermer l'espace de stockage
}

void loadMapSettings() {
  preferences.begin("mapSettings", true);  // Ouvrir en mode lecture l'espace de stockage "soundSettings"
  activeMapIndex = preferences.getInt("activeMapIndex", 0);  // Lire l'option de son, valeur par défaut 0
  preferences.end();  // Fermer l'espace de stockage
}

void saveSettings()
{
  saveSoundSettings();
  saveThemeSettings();
  saveMapSettings();
}

void loadSettings()
{
  loadSoundSettings();
  loadThemeSettings();
  loadMapSettings();
}
