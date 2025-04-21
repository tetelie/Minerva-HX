#include "mapping.h"
#include <Arduino.h>

int map_buffer = 0;
int mapping = 0;

void init_map(){
  readMapSwitch();
  map_buffer = mapping;
}
void readMapSwitch()
{
  mapping = digitalRead(32);
}

int updateMappingBuffer(){
  if(mapping != map_buffer)
  {
    // changement d'état
    map_buffer = mapping;
    return 1;
  }
  return 0;
}
