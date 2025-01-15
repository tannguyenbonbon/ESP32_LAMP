#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include "pin_config.h"
#include "project_info.h"
#include "serial_log.h"
#include "wifi_task.h"
#include "blynk_server.h"
#include "interrupt_task.h"
#include "relay_control.h"

EventGroupHandle_t event_group = NULL;

void setup() 
{
  event_group = xEventGroupCreate();

  #ifdef SERIAL_LOG_DEBUG
    Serial.begin(115200);
  #endif

  init_relay_gpio();

  enable_interrupt(BUTTON_PIN);

  wifi_init();

  // Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORDWORD);
}

void loop() 
{
  // Blynk.run();

  // control_interrupt(interruptFlag);

  // delay(10);
}