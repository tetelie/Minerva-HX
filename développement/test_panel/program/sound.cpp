#include "sound.h"
#include <Arduino.h>

bool soundEnabled = true;
int currentSound = 0;

void playMenuSound() {
  if (!soundEnabled) return;  // Si le son est désactivé, on ne joue rien

  int soundNote = NOTE_C5;

  soundNote = getSound(currentSound);

  tone(BUZZER_PIN, soundNote, 100);  // Jouer la note pendant 100ms
  delay(150);  // Pause pour que le son soit audible
  noTone(BUZZER_PIN);  // Arrêter le son
}

int getSound(int i)
{
  switch (i) {
    case 0: return NOTE_C5; break;
    case 1: return NOTE_D5; break;
    case 2: return NOTE_E5; break;
    case 3: return 3;  // Pas de son si "désactiver"
  }
}

void playSound(int note, int duration)
{
  if (!soundEnabled) return;  // Si le son est désactivé, on ne joue rien
  tone(BUZZER_PIN, getSound(note), duration);  // Jouer la note pendant 100ms
  delay(duration+50);  // Pause pour que le son soit audible
  noTone(BUZZER_PIN);  // Arrêter le son
}
