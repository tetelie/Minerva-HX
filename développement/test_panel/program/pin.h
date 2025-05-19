#pragma once
#include <Arduino.h>

// buzzer
#define BUZZER_PIN 25

// sliders
#define LEFT_SLIDER 22
#define RIGHT_SLIDER 0

// switch
#define MAPPING_SWITCH 6

// screen
#define TFT_CS   5
#define TFT_DC   15 // 2
#define TFT_RST  13 // 4

// joysticks
#define JOYSTICK_1_X 14
#define JOYSTICK_1_Y 12
#define JOYSTICK_1_Z 27

// expender
#define EXPENDER_SDA 21
#define EXPENDER_SCL 22

#define LED_4 5

// setup
void init_pin();
