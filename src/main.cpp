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
}

void loop() { }
