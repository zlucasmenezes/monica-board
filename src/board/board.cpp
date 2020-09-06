#include "board.h"

Board::Board(const char* host, int port) {
  this->host = host;
  this->port = port;
  this->authenticated = false;

  #if defined(ESP32)
  this->resolution = 4095;
  #else
  this->resolution = 1023;
  #endif
}

void Board::login(String board, String password) {
  HTTPClient http;
  http.begin(
    "http://" + (String)this->host + ":" + (String)this->port + "/api/board/auth"
  );
  http.addHeader("Content-Type", "application/json");

  String body = "{\"board\":\"" + board + "\",\"password\":\"" + password + "\"}";

  int httpResponseCode = http.POST(body);
  
  if (httpResponseCode > 0) {
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getString());
    
    String message = doc["message"];
    String boardId = doc["data"]["boardId"];
    String token = doc["data"]["token"];

    if (token != "null") {
      this->board = boardId;
      this->token = token;
      this->authenticated = true;
    }

    Serial.println(message);
  }

  http.end();
}

bool Board::isAuth() {
  return this->authenticated;
}

Devices Board::getDevices() {
  HTTPClient http;
  http.begin(
    "http://" + (String)this->host + ":" + (String)this->port + "/api/board/devices"
  );
  http.addHeader("Authorization", "Bearer " + this->token);

  Devices devices;

  JsonArray sensors;

  int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();

      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);

      sensors = doc["data"]["sensors"].as<JsonArray>();
      devices.sensors = sensors;
  }

  http.end();
  return devices;
}

void Board::insertSensorTSData(Sensor sensor, int value) {
  
  HTTPClient http;
  http.begin(
    "http://" + (String)this->host + ":" + (String)this->port + "/api/board/ts/" + sensor.getId()
  );
  http.addHeader("Authorization", "Bearer " + this->token);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"value\":" + (String)value + ", \"resolution\":" + (String)this->resolution + "}";

  int httpResponseCode = http.POST(body);

  if (httpResponseCode > 0) {
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getString());
    
    String message = doc["message"];
    Serial.println(sensor.getId() + " => " + message);
  }

  http.end();
};
