#include "menu.h"
#include "screen.h"
#include "theme.h"
#include "mapping.h"
#include "sound.h"

int selectedOption = 0;
String menuItems[] = {"Mappings", "Joysticks", "Sliders", "Sound", "Theme", "Quit"};
int menuSize = 6;  // Total des options
int visibleItems = 4;  // Nombre d'éléments visibles à l'écran

// Cette variable permet de contrôler quelle partie du menu est affichée
int scrollOffset = 0;

void drawMenu(int selected) {
  tft.fillScreen(ST77XX_BLACK);

  // En-tête info
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 10);
  tft.print("Map: ");
  tft.print(mappingOptions[activeMapIndex]);
  tft.print("  |  Color: ");
  tft.print(colorOptions[currentMainColor]);
  tft.print("  |  Sound: ");
  tft.print(currentSound);

  // Paramètres du menu
  int cardW = 200;
  int cardH = 35;
  int cardX = (240 - cardW) / 2 + 40;  // Centré horizontalement
  int yStart = 44;
  int spacing = 45;

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  for (int i = scrollOffset; i < scrollOffset + visibleItems && i < menuSize; i++) {
    int y = yStart + (i - scrollOffset) * spacing;

    if (i == selected) {
      // Carte sélectionnée
      tft.fillRoundRect(cardX, y, cardW, cardH, 8, getMainColor());
      tft.drawRoundRect(cardX, y, cardW, cardH, 8, ST77XX_WHITE);
      tft.setTextColor(ST77XX_WHITE);
    } else {
      // Carte normale
      tft.drawRoundRect(cardX, y, cardW, cardH, 8, ST77XX_WHITE);
      tft.setTextColor(ST77XX_WHITE);
    }

    // Centrage du texte
    String label = menuItems[i];
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(label, 0, 0, &x1, &y1, &w, &h);
    int textX = cardX + (cardW - w) / 2;
    int textY = y + (cardH - h) / 2;

    tft.setCursor(textX, textY);
    tft.print(label);
  }

  // Flèches de défilement
  if (scrollOffset > 0) {
    int t = 40;
    int u = 12;
    tft.fillTriangle(120+t, yStart - 35+u, 130+t, yStart - 20+u, 110+t, yStart - 20+u, ST77XX_WHITE);  // Flèche haut (pointe vers le haut)
  }

  if (scrollOffset + visibleItems < menuSize) {
    int arrowY = yStart + visibleItems * spacing - 6;
    int t = 40;
    tft.fillTriangle(120+t, arrowY + 20, 130+t, arrowY + 5, 110+t, arrowY + 5, ST77XX_WHITE);  // Flèche bas
  }
}

void navigateMenu(int direction) {
  selectedOption += direction;  // Déplace la sélection

  // Empêcher de sortir des limites du menu
  if (selectedOption < 0) {
    selectedOption = 0;
  } else if (selectedOption >= menuSize) {
    selectedOption = menuSize - 1;
  }

  // Ajuste le scrollOffset pour faire défiler le menu
  if (selectedOption < scrollOffset) {
    scrollOffset = selectedOption;  // Défile vers le haut
  } else if (selectedOption >= scrollOffset + visibleItems) {
    scrollOffset = selectedOption - visibleItems + 1;  // Défile vers le bas
  }

  // Empêche que scrollOffset dépasse la taille du menu
  if (scrollOffset + visibleItems > menuSize) {
    scrollOffset = menuSize - visibleItems;
  }
}
