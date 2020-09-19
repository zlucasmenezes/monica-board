#include <Arduino.h>

class Relay {
  private:
    String relay;
    int pin;
    bool nc;

  public:
    Relay(int pin, String relay, bool nc);
    String getId();
    void update(bool value);
};
