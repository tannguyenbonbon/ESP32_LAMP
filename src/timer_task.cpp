#include <Arduino.h>
#include "timer_task.h"

unsigned long long startTime = 0;
bool trigger_flag = false;
bool block_timer_task = false;

extern EventGroupHandle_t event_group;

TaskHandle_t myTaskHandle = NULL;

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

            if (myTaskHandle == NULL)
            {
                xTaskCreate(counter_task, "counter_task", 4096, NULL, 1, &myTaskHandle);
                Serial.printf("Timer Started: %lu hours\n", hour);
            }
        }
    }
    else
    {
        if(hour == 0)
        {
            block_timer_task = false;
            if (myTaskHandle != NULL) 
            {
                vTaskDelete(myTaskHandle);
                myTaskHandle = NULL;
                Serial.println("Cancel Timer");
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
}
