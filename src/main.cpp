#include <Arduino.h>
#include <SocketIoClient.h>

#include "environment.h"
#include "authentication.h"
#include "header.h"

#include "wifi/wifi.h"
#include "board/board.h"
#include "file-system/file-system.h"

Wifi wifi(WIFI_SSID, WIFI_PASSWORD);
Board board(SERVER_HOST, SERVER_PORT);
FileSystem fileSystem;

SocketIoClient io;

std::vector<Sensor> sensors;
std::vector<Relay> relays;

void joinRoom(const char *payload, size_t length)
{
  io.emit("join_room", ("\"board:" + board.getId() + "\"").c_str());
}

void updateRelay(const char *payload, size_t length)
{
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, payload);

  String id = doc["relay"];
  boolean value = doc["value"];

  for (size_t i = 0; i < relays.size(); i++)
  {
    String relay = relays.at(i).getId();
    if (relay == id)
    {
      relays.at(i).update(value);
      fileSystem.setRelayValue(relay, value);
    }
  }
}

void setupDevices(const char *payload, size_t length)
{
  Serial.println("[MAIN] Setting up devices");
  Devices devices = board.getDevices();

  sensors.clear();
  relays.clear();

  for (JsonVariant v : devices.sensors)
  {
    String sensor = v["sensor"];
    String type = v["type"];
    String input = v["input"];
    int pin = v["pin"];
    int pollTime = v["pollTime"];

    Serial.println("[MAIN] Sensor: " + sensor + " => Type: " + type + " | Input: " + input + " | Pin: " + String(pin) + " | Poll Time: " + String(pollTime));
    sensors.emplace_back(Sensor(pin, type, input, sensor, pollTime));
  }

  for (JsonVariant v : devices.relays)
  {
    String relay = v["relay"];
    int pin = v["pin"];
    boolean nc = v["nc"];
    int button = v["button"];

    Serial.println("[MAIN] Relay: " + relay + " => Pin: " + String(pin) + " | NC: " + nc + " | Button: " + button);
    relays.emplace_back(Relay(pin, relay, nc, button));
  }

  for (size_t i = 0; i < relays.size(); i++)
  {
    Relay relay = relays.at(i);
    io.on(relay.getId().c_str(), updateRelay);

    boolean value = fileSystem.getRelayValue(relay.getId());
    board.insertRelayTSData(relay.getId(), value);
    relay.update(value);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\nMONICA v" + String(VERSION));

  wifi.connect();

  while (!board.isAuth())
  {
    board.login(String(BOARD), String(BOARD_PASSWORD));
    delay(1000);
  }

#if defined(ESP8266)
  SPIFFS.begin();
#elif defined(ESP32)
  SPIFFS.begin(true);
#endif

  if (board.getId() != fileSystem.getBoard())
  {
    fileSystem.setBoard(board.getId());
  }

  setupDevices(NULL, 0);

  io.on("board_connected", joinRoom);
  io.on("update_devices", setupDevices);
  io.begin(SERVER_HOST, SERVER_PORT, ("/socket.io/?transport=websocket&board=" + board.getToken()).c_str());
}

void loop()
{
  io.loop();

  unsigned long currentMillis = millis();

  for (size_t i = 0; i < sensors.size(); i++)
  {
    if ((unsigned long)(currentMillis - sensors.at(i).previousMillis) >= sensors.at(i).getPollTime())
    {
      board.insertSensorTSData(sensors.at(i), sensors.at(i).getValue());
      sensors.at(i).previousMillis = currentMillis;
    }
  }
}
