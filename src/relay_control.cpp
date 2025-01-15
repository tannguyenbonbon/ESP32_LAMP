#include <Arduino.h>
#include "pin_config.h"

void control_relay(bool status)
{
  digitalWrite(RELAY_PIN, status ? HIGH : LOW);
}

void init_relay_gpio()
{
    pinMode(RELAY_PIN, OUTPUT);
    control_relay(LOW);         //TURN OFF RELAY
}