#include "relay.h"

Relay::Relay(int pin, String relay, bool nc) {
  this->pin = pin;
  this->relay = relay;
  this->nc = nc;

  pinMode(pin, OUTPUT);
}

String Relay::getId() {
  return this->relay;
}

void Relay::update(bool value) {
  if(this->nc) {
    digitalWrite(this->pin, !value);
  } else {
    digitalWrite(this->pin, value);
  }  
}
