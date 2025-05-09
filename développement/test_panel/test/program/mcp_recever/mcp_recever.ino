void setup() {
  Serial.begin(115200);          // Moniteur série USB
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // RX2=GPIO16, TX2=GPIO17

  Serial.println("Récepteur prêt. En attente de données sur Serial2...");
}


// packet

// ID | MSG

/*

    ID:0                      // TURN OFF WIFI
    ID:1                      // TURN ON  WIFI
    ID:2 wifi_id>password     // configure WIFI
    ID:3 message              // transmit message via current wifi
*/

void loop() {
  if (Serial2.available()) {
    String message = Serial2.readStringUntil('\n');  // Lecture ligne par ligne
    Serial.print("Reçu : ");
    Serial.println(message);  // Affiche ce qui a été reçu
  }
}
