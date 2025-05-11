#include "pin.h"
#include "sound.h"
#include "pin.h"
#include "expender.h"

void init_pin()
{
  pinMode(BUZZER_PIN, OUTPUT);            // buzzer
  pinMode(LEFT_SLIDER, INPUT);            // left slider
  pinMode(RIGHT_SLIDER, INPUT);           // right slider
  mcp.pinMode(MAPPING_SWITCH, INPUT_PULLUP);  // mapping switch
  pinMode(JOYSTICK_1_Z, INPUT_PULLUP);    // joystick 1 click
}
