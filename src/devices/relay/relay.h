#include <Arduino.h>

class Relay {
  private:
    String relay;
    int pin;
    boolean nc;

  public:
    Relay(int pin, String relay, boolean nc);
    String getId();
    void update(boolean value);
};
