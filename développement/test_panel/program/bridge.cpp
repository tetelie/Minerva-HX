#include "bridge.h"

void initBridge()
{
  Serial2.begin(9600, SERIAL_8N1, 26, 25); // RX = 26, TX = 25
}
