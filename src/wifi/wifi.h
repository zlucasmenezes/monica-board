#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#elif defined(ESP32)
#include <HTTPClient.h>
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
    bool isConnected();
};
