#include "menu.h"
#include "screen.h"

int selectedOption = 0;
String menuItems[] = {"Mappings", "Joystick", "Potentiometer", "Sound Settings", "Color Settings", "Quit"};
int menuSize = 6;  // Total des options
int visibleItems = 4;  // Nombre d'éléments visibles à l'écran

// Cette variable permet de contrôler quelle partie du menu est affichée
int scrollOffset = 0;

void drawMenu(int selected) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);

  int yStart = 60;  // Position de départ en Y
  int spacing = 40;  // Espacement entre les options
  int xLeft = 30; // Marge gauche

  // Affiche les options visibles
  for (int i = scrollOffset; i < scrollOffset + visibleItems && i < menuSize; i++) {
    int y = yStart + (i - scrollOffset) * spacing;

    if (i == selected) {
      tft.fillRect(xLeft - 10, y - 5, 180, 30, ST77XX_BLUE);  // Fond bleu pour l'élément sélectionné
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLUE);
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    }

    tft.setCursor(xLeft, y);
    tft.print(menuItems[i]);
  }

  // Dessiner une flèche vers le haut (si possible de défiler vers le haut)
  if (scrollOffset > 0) {
    tft.fillTriangle(110, 40, 120, 30, 130, 40, ST77XX_WHITE);  // Flèche vers le haut
  }

  // Dessiner une flèche vers le bas (si possible de défiler vers le bas)
  if (scrollOffset + visibleItems < menuSize) {
    tft.fillTriangle(110, yStart + visibleItems * spacing + 10, 120, yStart + visibleItems * spacing + 20, 130, yStart + visibleItems * spacing + 10, ST77XX_WHITE);  // Flèche vers le bas
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
