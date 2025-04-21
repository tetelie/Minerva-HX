#include "menu_theme.h"
#include "screen.h"
#include "sound.h"
#include "pin.h"
#include "settings.h"
#include "menu.h"
#include "theme.h"

int visibleItems1 = 4;  // Nombre d'éléments visibles sur l'écran
int scrollOffset1 = 0;  // Offset du défilement


// Fonction pour afficher le menu de thème avec défilement
void showThemeMenu(String* soundOptions, int soundMenuSize, int yStart, int spacing, int xLeft) {
    tft.fillScreen(ST77XX_BLACK);

    // Affichage des flèches de défilement
    if (scrollOffset1 > 0) {
      tft.fillTriangle(110, 40, 120, 30, 130, 40, ST77XX_WHITE);  // Flèche vers le haut
    }
    if (scrollOffset1 + visibleItems1 < colorsCount) {
      tft.fillTriangle(110, yStart + visibleItems1 * spacing + 10, 120, yStart + visibleItems1 * spacing + 20, 130, yStart + visibleItems1 * spacing + 10, ST77XX_WHITE);  // Flèche vers le bas

    }

    // Affichage des options du menu
    for (int i = scrollOffset1; i < scrollOffset1 + visibleItems1 && i < colorsCount; i++) {
        int y = yStart + (i - scrollOffset1) * spacing;
        if (i == currentMainColor) {
            tft.fillRect(xLeft - 10, y - 5, 180, 30, colors[i]);
            tft.setTextColor(ST77XX_WHITE, colors[i]);
        } else {
            tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
        }

        tft.setCursor(xLeft, y);
        tft.print(soundOptions[i]);
    }
}

// Fonction pour gérer la sélection et le défilement du menu
void themeSettingsMenu() {
    int soundMenuSize = colorsCount;  // Utilisation de colorsCount pour déterminer la taille du menu

    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    int yStart = 60;
    int spacing = 40;
    int xLeft = 30;

    // Affichage initial du menu de thème
    showThemeMenu(colorOptions, soundMenuSize, yStart, spacing, xLeft);
    delay(150);
    bool inThemeMenu = true;
    while (inThemeMenu) {
        int xVal = analogRead(JOYSTICK_1_X);  // Lecture du joystick X
        int yVal = analogRead(JOYSTICK_1_Y);  // Lecture du joystick Y
        int zVal = digitalRead(JOYSTICK_1_Z); // Lecture du bouton

        // Joystick vers le haut
        if (yVal > 3000) {
            currentMainColor--;
            if (currentMainColor < 0) currentMainColor = colorsCount - 1;  // Retour à la fin du menu
            if (currentMainColor < scrollOffset1) scrollOffset1 = currentMainColor;  // Défilement vers le haut
            playMenuSound();
            showThemeMenu(colorOptions, soundMenuSize, yStart, spacing, xLeft);
            delay(150);
        }
        // Joystick vers le bas
        else if (yVal < 1000) {
            currentMainColor++;
            if (currentMainColor >= colorsCount) currentMainColor = 0;  // Retour au début du menu
            if (currentMainColor >= scrollOffset1 + visibleItems1) scrollOffset1 = currentMainColor - visibleItems1 + 1;  // Défilement vers le bas
            playMenuSound();
            showThemeMenu(colorOptions, soundMenuSize, yStart, spacing, xLeft);
            delay(150);
        }

        // Bouton pressé
        if (zVal == LOW) {
            tft.fillScreen(ST77XX_BLACK);

            // Change la couleur principale (sélectionnée)
            //currentMainColor = colors[currentMainColor];
            saveSettings();
            playMenuSound();  // Son lors de la sélection
            inThemeMenu = false;  // Quitter le menu
            drawMenu(selectedOption);  // Retour au menu principal
        }

        delay(50);
    }
}
