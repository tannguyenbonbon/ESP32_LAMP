#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include "pin_config.h"
#include "project_info.h"
#include "wifi_task.h"
#include "blynk_server.h"
#include "interrupt_task.h"
#include "timer_task.h"
#include "gpio_task.h"

EventGroupHandle_t event_group = NULL;

void setup() 
{
  event_group = xEventGroupCreate();

  Serial.begin(115200);
  Serial.println("");

  init_gpio();

  start_relay_control();

  start_wifi();

  start_blynk_server();

}

void loop() 
{
}