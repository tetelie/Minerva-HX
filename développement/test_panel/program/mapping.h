#pragma once

extern int currentMap;
extern int map_buffer;
extern int mapping;

void init_map();
void readMapSwitch();
int updateMapping();
void start_map();
