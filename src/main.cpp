#include <Arduino.h>
#include "environment.h"
#include "authentication.h"

#include "wifi/wifi.h"
#include "board/board.h"

Wifi wifi(WIFI_SSID, WIFI_PASSWORD);
Board board(SERVER_HOST, SERVER_PORT);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nMONICA v" + String(VERSION));

  wifi.connect();

  while(!board.isAuth()) {
    board.login(String(BOARD), String(BOARD_PASSWORD));
  }

  Devices devices = board.getDevices();

  for(JsonVariant v : devices.sensors) {
      String sensor = v["sensor"];
      String type = v["type"];
      String input = v["input"];
      int pin = v["pin"];
      int pollTime = v["pollTime"];

      Serial.println(sensor + " => Type: " + type + " | Input: " + input + " | Pin: " + String(pin) + " | Poll Time: " + String(pollTime));
  }
}

void loop() { }
