#include "startup.h"
#include "screen.h"
#include "Arduino.h"
#include "logo.h"
#include "sound.h"

void showLogoWithMelody() {
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(96, 56, logo, 128, 128);

  // Notes et durées correspondantes
  int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5};
  int durations[] = {200, 200, 200, 200, 300, 300};

  unsigned long startTime = millis();
  int noteIndex = 0;
  bool notePlaying = false;
  unsigned long noteStartTime = 0;

  while (millis() - startTime < 3000) {
    if (!notePlaying && noteIndex < 6) {
      if(soundEnabled)tone(BUZZER_PIN, melody[noteIndex], durations[noteIndex]);
      noteStartTime = millis();
      notePlaying = true;
    }

    if (notePlaying && millis() - noteStartTime > durations[noteIndex] * 1.3) {
      noTone(BUZZER_PIN);
      noteIndex++;
      notePlaying = false;
    }
  }
  noTone(BUZZER_PIN); // arrêt de sécurité
}
