#include <Arduino.h>
#include "environment.h"

#include "wifi/wifi.h"

Wifi wifi(WIFI_SSID, WIFI_PASSWORD);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nMONICA v" + String(VERSION));

  wifi.connect();
}

void loop() { }
