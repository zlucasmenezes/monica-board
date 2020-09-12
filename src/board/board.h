#include <Arduino.h>
#include <ArduinoJson.h>
#include "header.h"

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#else
#error "Please use an interface such as ESP8266 or ESP32"
#endif

struct Devices {
  JsonArray sensors;
};

class Board{
  private:
    const char* host;
    int port;
    int resolution;

    String board;
    String token;

    bool authenticated;

  public:
    Board(const char* host, int port);

    void login(String board, String password);
    bool isAuth();
    Devices getDevices();
    void insertSensorTSData(Sensor sensor, int value);
};
