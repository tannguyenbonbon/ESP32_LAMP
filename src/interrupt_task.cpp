#include <Arduino.h>
#include "pin_config.h"
#include "blynk_server.h"

volatile bool interruptFlag = false;
bool relay_status = false;

void enable_interrupt(int interrupt_pin);
void disable_interrupt(int interrupt_pin);

static void IRAM_ATTR handleInterrupt() 
{
  disable_interrupt(BUTTON_PIN);
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

void control_relay(bool status)
{
  digitalWrite(RELAY_PIN, status ? HIGH : LOW);
}

static void control_interrupt_task(void *pvParameters)
{
  while (true)
  {
    if (interruptFlag)
    {
      vTaskDelay(pdMS_TO_TICKS(100));
      //-----------------------------
      relay_status = !relay_status;
      Serial.printf("RELAY STATUS: %d\n", relay_status);
      control_relay(relay_status);
      // sync_VirtualPin(V0, relay_status);
      //-----------------------------
      enable_interrupt(BUTTON_PIN);
      interruptFlag = false;
    }
  }
  vTaskDelete(NULL);
}

void start_relay_control()
{
  xTaskCreate(control_interrupt_task, "control_interrupt_task", 4096, NULL, 1, NULL);
  enable_interrupt(BUTTON_PIN);
}

