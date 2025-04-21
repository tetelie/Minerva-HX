#pragma once
#include <Arduino.h>

#define BUZZER_PIN 13
#define LEFT_SLIDER 15
#define RIGHT_SLIDER 0
#define MAPPING_SWITCH 32

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

#define JOYSTICK_1_X 14
#define JOYSTICK_1_Y 12
#define JOYSTICK_1_Z 27

void init_pin();
