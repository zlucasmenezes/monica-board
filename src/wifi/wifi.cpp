#include <Arduino.h>
#include "wifi.h"

Wifi::Wifi(const char* ssid, const char* password){
  this->ssid = ssid;
  this->password = password;
};

void Wifi::connect(){
  Serial.print("Connecting to " + String(ssid) + " ");

  WiFi.begin(ssid, password);
  while (!this->isConnected()) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" Connected");
};

boolean Wifi::isConnected(){
  return WiFi.status() == WL_CONNECTED;
};
