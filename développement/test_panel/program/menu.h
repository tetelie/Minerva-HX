#pragma once
#include <Arduino.h>

extern int selectedOption;
extern String menuItems[];
extern int menuSize;

void drawMenu(int);
void navigateMenu(int direction);
