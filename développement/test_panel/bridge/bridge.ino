void setup() {
  Serial.begin(115200);  // debug USB
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX, TX (inverse de l’autre)
}

void loop() {
  if (Serial2.available()) {
    String received = Serial2.readStringUntil('\n');
    int value = received.toInt();  // conversion en int
    Serial.println("Reçu : " + String(value));

    // Ici, tu peux contrôler un servo, envoyer en WiFi, etc.
  }
}
