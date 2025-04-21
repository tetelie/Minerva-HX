#include "pin.h"
#include "buzzer.h"
#include "joystick.h"

void init_pin()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(15, INPUT);        // left slider
  pinMode(0, INPUT);         // right slider
  pinMode(32, INPUT_PULLUP); // mapping switch
  pinMode(xyzPins1[2], INPUT_PULLUP);
}
