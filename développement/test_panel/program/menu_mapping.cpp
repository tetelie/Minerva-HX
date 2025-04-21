#include "menu_mapping.h"
#include "screen.h"
#include "sound.h"
#include "pin.h"
#include "settings.h"
#include "menu.h"
#include "theme.h"
#include "mapping.h"

int visibleItems2 = 4;  // Nombre d'éléments visibles sur l'écran
int scrollOffset2 = 0;  // Offset du défilement


// Fonction pour afficher le menu de thème avec défilement
void showMappingMenu(String* soundOptions, int soundMenuSize, int yStart, int spacing, int xLeft) {
    tft.fillScreen(ST77XX_BLACK);

    // Affichage des flèches de défilement
    if (scrollOffset2 > 0) {
      tft.fillTriangle(110, 40, 120, 30, 130, 40, ST77XX_WHITE);  // Flèche vers le haut
    }
    if (scrollOffset2 + visibleItems2 < mappingCount) {
      tft.fillTriangle(110, yStart + visibleItems2 * spacing + 10, 120, yStart + visibleItems2 * spacing + 20, 130, yStart + visibleItems2 * spacing + 10, ST77XX_WHITE);  // Flèche vers le bas

    }

    // Affichage des options du menu
    for (int i = scrollOffset2; i < scrollOffset2 + visibleItems2 && i < mappingCount; i++) {
        int y = yStart + (i - scrollOffset2) * spacing;
        if (i == activeMapIndex) {
            tft.fillRect(xLeft - 10, y - 5, 180, 30, getMainColor());
            tft.setTextColor(ST77XX_WHITE, getMainColor());
        } else {
            tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
        }

        tft.setCursor(xLeft, y);
        tft.print(mappingOptions[i]);
    }
}


// Fonction pour gérer la sélection et le défilement du menu
void mappingSettingsMenu() {
    int soundMenuSize = mappingCount;  // Utilisation de mappingCount pour déterminer la taille du menu

    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    int yStart = 60;
    int spacing = 40;
    int xLeft = 30;

    // Affichage initial du menu de thème
    showMappingMenu(mappingOptions, soundMenuSize, yStart, spacing, xLeft);
    delay(150);
    bool inThemeMenu = true;
    while (inThemeMenu) {
        int xVal = analogRead(JOYSTICK_1_X);  // Lecture du joystick X
        int yVal = analogRead(JOYSTICK_1_Y);  // Lecture du joystick Y
        int zVal = digitalRead(JOYSTICK_1_Z); // Lecture du bouton

        // Joystick vers le haut
        if (yVal > 3000) {
            activeMapIndex--;
            if (activeMapIndex < 0) activeMapIndex = mappingCount - 1;  // Retour à la fin du menu
            if (activeMapIndex < scrollOffset2) scrollOffset2 = activeMapIndex;  // Défilement vers le haut
            playMenuSound();
            showMappingMenu(mappingOptions, soundMenuSize, yStart, spacing, xLeft);
            delay(150);
        }
        // Joystick vers le bas
        else if (yVal < 1000) {
            activeMapIndex++;
            if (activeMapIndex >= mappingCount) activeMapIndex = 0;  // Retour au début du menu
            if (activeMapIndex >= scrollOffset2 + visibleItems2) scrollOffset2 = activeMapIndex - visibleItems2 + 1;  // Défilement vers le bas
            playMenuSound();
            showMappingMenu(mappingOptions, soundMenuSize, yStart, spacing, xLeft);
            delay(150);
        }

        // Bouton pressé
        if (zVal == LOW) {
            tft.fillScreen(ST77XX_BLACK);

            saveSettings();
            playMenuSound();  // Son lors de la sélection
            inThemeMenu = false;  // Quitter le menu
            drawMenu(selectedOption);  // Retour au menu principal
        }

        delay(50);
    }
}
