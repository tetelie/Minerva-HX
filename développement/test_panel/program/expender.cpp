#include "expender.h"

MCP23017 mcp(MCP23017_ADDR);

void init_expender()
{
  Wire.begin(EXPENDER_SDA, EXPENDER_SCL);
  mcp.init();
  Serial.println("MCP23017 initialisé.");
}
