#pragma once

#include <stdbool.h>


// Notes musicales
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784

#define BUZZER_PIN 13

// Variables pour le son
extern bool soundEnabled;
extern int currentSound;

void playMenuSound();
