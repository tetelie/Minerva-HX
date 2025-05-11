#include "map_test.h"
#include <Arduino.h>
#include "screen.h"
#include "theme.h"
#include <WiFi.h>
#include <esp_now.h>
#include "pin.h"

uint8_t receiverMAC[] = {0xF4, 0x65, 0x0B, 0x41, 0x50, 0xDC};

typedef struct {
  int value;
} DataPacket;

DataPacket dataToSend;

void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Envoi : ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Succès" : "Échec");
}


void testMap_setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(100);
  Serial.println("Mode STA activé. MAC : " + WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'init ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erreur d'ajout de peer");
    return;
  }


  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(getMainColor());
  tft.setCursor(0, 10);
  tft.println("Test Map");

}

void testMap_disable()
{
  esp_now_deinit();            // Stoppe ESP-NOW
  WiFi.mode(WIFI_OFF);         // Désactive le Wi-Fi

}

void testMap_loop()
{

  static int lastX = -1;


  static int lastXVal = -1;

  int xVal = analogRead(LEFT_SLIDER);

  int xBarLength = map(xVal, 0, 4095, 0, 160);

    // Mise à jour intelligente de la jauge X
    if (xBarLength != lastX) {
      if (xBarLength > lastX) {
        tft.fillRect(40 + lastX, 50, xBarLength - lastX, 10, getMainColor());
      } else {
        tft.fillRect(40 + xBarLength, 50, lastX - xBarLength, 10, ST77XX_BLACK);
      }
      lastX = xBarLength;
    }

    // Affichage intelligent des valeurs X
    if (xVal != lastXVal) {
      tft.fillRect(210, 50, 50, 20, ST77XX_BLACK);
      tft.setCursor(210, 50);
      tft.print(xVal);
      lastXVal = xVal;
    }


    dataToSend.value = xVal;

    Serial.print(xVal);
    esp_now_send(receiverMAC, (uint8_t*)&dataToSend, sizeof(dataToSend));

    delay(50);

}
