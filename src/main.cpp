#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include "pin_config.h"
#include "project_info.h"
#include "wifi_task.h"
#include "blynk_server.h"
#include "interrupt_task.h"

EventGroupHandle_t event_group = NULL;

void setup() 
{
  event_group = xEventGroupCreate();

  Serial.begin(115200);
  Serial.println("");

  start_relay_control();

  start_wifi();

  // Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORDWORD);
}

void loop() 
{
  // Blynk.run();

  // control_interrupt(interruptFlag);

  // delay(10);
}