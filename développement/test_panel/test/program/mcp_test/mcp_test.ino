#include <Wire.h>
#include <MCP23017.h>

// Adresse I2C du MCP23017 (par défaut 0x20)
#define MCP23017_ADDR 0x20
#define LED 7  // GPA7 sur MCP23017

MCP23017 mcp(MCP23017_ADDR);

void setup() {
  Wire.begin(21, 22);            // SDA = GPIO21, SCL = GPIO22
  Serial.begin(115200);          // USB debug
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX2=GPIO16, TX2=GPIO17

  delay(200);

  mcp.init();                    // Initialisation du MCP23017
  mcp.pinMode(LED, OUTPUT);      // LED sur GPA7 en sortie

  Serial.println("MCP23017 initialisé. Communication Serial2 active.");
}

void loop() {
  mcp.digitalWrite(LED, HIGH);
  Serial.println("LED ON");
  Serial2.println("LED ON");     // Envoie à l'autre ESP32
  delay(500);

  mcp.digitalWrite(LED, LOW);
  Serial.println("LED OFF");
  Serial2.println("LED OFF");
  delay(500);
}
