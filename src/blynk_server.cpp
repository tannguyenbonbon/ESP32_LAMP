#include "blynk_server.h"
#include "project_info.h"
#include <BlynkSimpleEsp32.h>
#include "interrupt_task.h"
#include "timer_task.h"

extern EventGroupHandle_t event_group;

extern bool relay_status;

void sync_VirtualPin(int PIN, int status) 
{
  Blynk.virtualWrite(PIN, status);
}

static void reset_VirtualPin()
{
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
}

static void init_blynk_task(void *pvParameters)
{
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();
  vTaskDelay(pdMS_TO_TICKS(1000));
  reset_VirtualPin();

  while(true)
  {
    Blynk.run();
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  vTaskDelete(NULL);
}

void start_blynk_server()
{
  xTaskCreate(init_blynk_task, "init_blynk_task", 4096, NULL, 3, NULL);
}

BLYNK_WRITE(V0) {
    int pinValue = param.asInt();
    Serial.printf("V0: %d\n", pinValue);
    relay_status = pinValue ? true:false;
    control_relay(relay_status);
}

BLYNK_WRITE(V1) {
    int pinValue = param.asInt();
    Serial.printf("V1: %d\n", pinValue);
    start_timer(pinValue);
}
