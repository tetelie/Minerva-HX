#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>  // Remplace Servo.h par ESP32Servo.h

Servo myServo;
const int servoPin = 25;

typedef struct {
  int value;
} DataPacket;

DataPacket receivedData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  int angle = map(receivedData.value, 0, 4095, 0, 180);
  myServo.write(angle);
  Serial.println("Angle reçu : " + String(angle));
}

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);    // 50Hz pour les servos classiques
  myServo.attach(servoPin, 500, 2400); // plage PWM personnalisée pour ESP32

  WiFi.mode(WIFI_STA);
  Serial.println("Mode STA activé. MAC : " + WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'init ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // rien ici
}
