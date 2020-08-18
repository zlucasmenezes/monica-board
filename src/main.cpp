#include <Arduino.h>
#include "wifi/wifi.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";

Wifi wifi(ssid, password);

void setup() {
  Serial.begin(115200);

  Serial.println("\n\nMONICA");
  Serial.println("======\n");

  wifi.connect();
}

void loop() {
  Serial.println(wifi.isConnected());
}
