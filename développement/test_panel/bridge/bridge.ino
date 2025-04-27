void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    Serial.println("Reçu : " + msg);
  }
}
