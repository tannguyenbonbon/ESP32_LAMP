#include <Arduino.h>
#include "timer_task.h"
#include "pin_config.h"

unsigned long long startTime = 0;
bool trigger_flag = false;
bool block_timer_task = false;

extern EventGroupHandle_t event_group;

TaskHandle_t timerTaskHandle = NULL;
TaskHandle_t ledTaskHandle = NULL;

uint64_t timeout_ms = 0;

static void set_timer_timeout(uint64_t hour)
{
    timeout_ms = (uint64_t)hour * 60 * 60 * 1000;

    // timeout_ms = 0.01 * 60 * 60 * 1000;

    // Serial.printf("Timer set: %lu ms - %.2f s - %.2f m - %.2f h\n",
    //             timeout_ms,
    //             timeout_ms / 1000.0,
    //             (timeout_ms / 1000.0) / 60.0, 
    //             ((timeout_ms / 1000.0) / 60.0) / 60.0);

}

static void timer_callback()
{
    Serial.println("Timer called");   
    stop_timer();
}

static void timer_led_indicate_task(void *pvParameters)
{
    bool led_st = 0;
    while(true)
    {
        led_st = !led_st;
        digitalWrite(TIMER_LED_PIN, led_st);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    digitalWrite(TIMER_LED_PIN, LOW);
    vTaskDelete(NULL);
}

static void counter_task(void *pvParameters)
{
    while(true)
    {
        // Serial.printf("Time: %lu\n", millis());
        if(!trigger_flag && ((millis() - startTime) > timeout_ms))
        {
            timer_callback();
            if(trigger_flag)
            {
                break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void start_timer(uint64_t hour)
{
    if (!block_timer_task)
    {
        startTime = millis();
        set_timer_timeout(hour);

        if(hour > 0)
        {
            block_timer_task = true;
            trigger_flag = false;

            if (timerTaskHandle == NULL)
            {
                xTaskCreate(counter_task, "counter_task", 4096, NULL, 1, &timerTaskHandle);
            }
            if(ledTaskHandle == NULL)
            {
                xTaskCreate(timer_led_indicate_task, "timer_led_indicate_task", 4096, NULL, 4, &ledTaskHandle);
                Serial.printf("Timer Started: %lu hours\n", hour);
            }
        }
    }
    else
    {
        if(hour == 0)
        {
            block_timer_task = false;
            if (timerTaskHandle != NULL) 
            {
                vTaskDelete(timerTaskHandle);
                timerTaskHandle = NULL;
            }
            if(ledTaskHandle != NULL)
            {
                digitalWrite(TIMER_LED_PIN, LOW);
                vTaskDelete(ledTaskHandle);
                ledTaskHandle = NULL;
            }
        }
        else
        {
            Serial.println("Another Timer Already Started !");
        }
    }
}

void stop_timer()
{
    trigger_flag = true;
    block_timer_task = false;

    if(ledTaskHandle != NULL)
    {
        digitalWrite(TIMER_LED_PIN, LOW);
        vTaskDelete(ledTaskHandle);
        ledTaskHandle = NULL;
    }
}
