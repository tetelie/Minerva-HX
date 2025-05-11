#pragma once
#include <Arduino.h>

extern int currentMap;
extern int map_buffer;
extern int mapping;
extern int activeMapIndex;

extern String mappingOptions[];
extern int mappingCount;


void init_map();
void readMapSwitch();
int updateMapping();
void start_map();
void disable_map();
void run_map();