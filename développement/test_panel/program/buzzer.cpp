#include "buzzer.h"
#include <Arduino.h>

bool soundEnabled = true;
int currentSound = 0;

void playMenuSound() {
  if (!soundEnabled) return;  // Si le son est désactivé, on ne joue rien

  int soundNote = NOTE_C5;
  switch (currentSound) {
    case 0: soundNote = NOTE_C5; break;
    case 1: soundNote = NOTE_D5; break;
    case 2: soundNote = NOTE_E5; break;
    case 3: return;  // Pas de son si "désactiver"
  }

  tone(BUZZER_PIN, soundNote, 100);  // Jouer la note pendant 100ms
  delay(150);  // Pause pour que le son soit audible
  noTone(BUZZER_PIN);  // Arrêter le son
}
