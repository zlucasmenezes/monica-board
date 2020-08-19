#include <Arduino.h>
#include <WiFi.h>

class Wifi{
  private:
    const char* ssid;
    const char* password;

  public:
    Wifi(const char* ssid, const char* password);

    void connect();
    bool isConnected();
};
