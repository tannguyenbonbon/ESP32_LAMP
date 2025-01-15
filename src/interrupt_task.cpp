#include <Arduino.h>
#include "pin_config.h"
#include "relay_control.h"

SemaphoreHandle_t relayMutex;

volatile bool interruptFlag = false;

static void IRAM_ATTR handleInterrupt() 
{
  interruptFlag = true;
}

void enable_interrupt(int interrupt_pin)
{
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), handleInterrupt, RISING);
}

void disable_interrupt(int interrupt_pin)
{
  detachInterrupt(interrupt_pin);
}

static void control_interrupt(bool flag)
{
  if(flag)
  {
    disable_interrupt(BUTTON_PIN);
    delay(100);
    enable_interrupt(BUTTON_PIN);
    //-----------------------------
    // relay_status = !relay_status;
    // control_relay(relay_status);
    // syncVirtualPin(V0, relay_status);
    //-----------------------------
    interruptFlag = false;
  }
}