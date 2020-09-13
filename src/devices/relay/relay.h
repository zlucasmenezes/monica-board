#include <Arduino.h>

class Relay {
  private:
    String relay;
    int pin;

  public:
    Relay(int pin, String relay);
    String getId();
};
