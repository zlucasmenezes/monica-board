#include "relay.h"

Relay::Relay(int pin, String relay) {
  this->pin = pin;
  this->relay = relay;

  pinMode(pin, OUTPUT);
}

String Relay::getId() {
  return this->relay;
}

void Relay::update(bool value) {
  digitalWrite(this->pin, value);
}
