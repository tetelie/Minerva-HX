#include "pin.h"
#include "buzzer.h"
#include "joystick.h"

void init_pin()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(15, INPUT);
  pinMode(0, INPUT);
  pinMode(32, INPUT_PULLUP);
  pinMode(xyzPins1[2], INPUT_PULLUP);
}
