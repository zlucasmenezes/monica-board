#include "relay.h"

Relay::Relay(int pin, String relay) {
  this->pin = pin;
  this->relay = relay;

  pinMode(pin, OUTPUT);
}

String Relay::getId() {
  return this->relay;
}
