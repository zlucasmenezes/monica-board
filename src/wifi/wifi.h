#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Please use an interface such as ESP8266 or ESP32"
#endif

class Wifi{
  private:
    const char* ssid;
    const char* password;

  public:
    Wifi(const char* ssid, const char* password);

    void connect();
    boolean isConnected();
};
