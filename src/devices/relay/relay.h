#include <Arduino.h>

class Relay
{
private:
  String relay;
  int pin;
  boolean nc;
  int button;

public:
  Relay(int pin, String relay, boolean nc, int button);
  String getId();
  void update(boolean value);
};
