#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include "pin.h"

#define MCP23017_ADDR 0x20

extern MCP23017 mcp;
 

void init_expender();
