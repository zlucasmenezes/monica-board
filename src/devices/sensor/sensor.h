#include <Arduino.h>

class Sensor
{
private:
  String sensor;
  int pin;
  String type;
  String input;
  int pollTime;

  int getAnalogValue();

public:
  unsigned long previousMillis;

  Sensor(int pin, String type, String input, String sensor, int pollTime);
  String getId();
  int getPollTime();
  int getValue();
};
