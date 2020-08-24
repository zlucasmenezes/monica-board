#include <Arduino.h>

class Sensor {
  private:
    String sensor;
    int pin;
    String type;
    String input;

    int getAnalogValue();

  public:
    int pollTime;
    unsigned long previousMillis;

    Sensor(int pin, String type, String input, String sensor, int pollTime);
    int getValue();
};
