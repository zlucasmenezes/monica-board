#include "sensor.h"

Sensor::Sensor(int pin, String type, String input, String sensor, int pollTime) {
  this->pin = pin;
  this->type = type;
  this->input = input;
  this->sensor = sensor;
  this->pollTime = pollTime;
  this->previousMillis = 0;

  pinMode(pin, INPUT);
}

String Sensor::getId() {
  return this->sensor;
}

int Sensor::getPollTime() {
  return this->pollTime;
}

int Sensor::getValue() {
  if (this->input == "Analog") {
    return this->getAnalogValue();
  }

  return this->getAnalogValue();
}

int Sensor::getAnalogValue() {
  int n = 1;
  float samples[n];

  for (int i = 0; i < n; i++) {
    samples[i] = analogRead(this->pin);
  }

  float avg = 0;
  for (int i = 0; i < n; i++) {
    avg += samples[i];
  }
  avg /= n;

  int value = avg;
  return value;
}
