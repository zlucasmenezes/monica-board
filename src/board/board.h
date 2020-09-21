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
  JsonArray relays;
};

class Board{
  private:
    const char* host;
    int port;
    int resolution;

    String board;
    String token;

    boolean authenticated;

  public:
    Board(const char* host, int port);

    void login(String board, String password);
    boolean isAuth();
    Devices getDevices();
    void insertSensorTSData(Sensor sensor, int value);
    void insertRelayTSData(String relay, boolean value);
    String getId();
    String getToken();
};
