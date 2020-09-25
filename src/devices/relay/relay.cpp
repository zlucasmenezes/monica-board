#include "relay.h"

Relay::Relay(int pin, String relay, boolean nc, int button)
{
  this->pin = pin;
  this->relay = relay;
  this->nc = nc;
  this->button = button;

  pinMode(pin, OUTPUT);
  pinMode(button, INPUT);
}

String Relay::getId()
{
  return this->relay;
}

void Relay::update(boolean value)
{
  if (this->nc)
  {
    digitalWrite(this->pin, !value);
  }
  else
  {
    digitalWrite(this->pin, value);
  }
}
