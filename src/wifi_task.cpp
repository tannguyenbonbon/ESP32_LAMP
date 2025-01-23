#include <WiFi.h>
#include <WiFiClient.h>

#include "project_info.h"

const char *SSID     =              "CENTRAL SPACE 69L1B";
const char *PASSWORD =              "central69";

// const char *SSID     =              "Tân Nguyễn";
// const char *PASSWORD =              "123456677";

#define CONNECTION_TIMEOUT_MS       10000       //* 10s
#define RETRY_CONNECTION_AFTER_MS   60000       //* 60s
#define DELAY_CHECK_WIFI_STATUS     1000        //* 5s

extern EventGroupHandle_t event_group;

static void check_wifi_status_task(void *pvParameters)
{
    while (true)
    {
        EventBits_t bits = xEventGroupGetBits(event_group);

        if (WiFi.status() == WL_CONNECTED)
        {
            if(!(bits & WIFI_CONNECTED_BIT))
            {
                Serial.println("SET WIFI_CONNECTED_BIT");
                xEventGroupSetBits(event_group, WIFI_CONNECTED_BIT);
                xEventGroupClearBits(event_group, WIFI_DISCONNECTED_BIT);
            }
        }
        else
        {
            if(!(bits & WIFI_DISCONNECTED_BIT))
            {
                Serial.println("SET WIFI_DISCONNECTED_BIT");
                xEventGroupSetBits(event_group, WIFI_DISCONNECTED_BIT);
                xEventGroupClearBits(event_group, WIFI_CONNECTED_BIT);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(DELAY_CHECK_WIFI_STATUS));
    }
    
    vTaskDelete(NULL);
}

static void init_wifi_task()
{
    xTaskCreate(check_wifi_status_task, "check_wifi_status_task", 4096, NULL, 1, NULL);
}

void start_wifi()
{
    Serial.printf("Connecting to Wi-Fi: %s ", SSID);

    WiFi.begin(SSID, PASSWORD);

    unsigned long startAttemptTime = millis();
    const unsigned long connectionTimeout = CONNECTION_TIMEOUT_MS;

    while (true)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.printf("\nConnected to %s\n", SSID);
            break;
        }

        Serial.print(".");

        if (millis() - startAttemptTime > connectionTimeout)
        {
            Serial.println("\nConnection timeout! Retrying later");
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
    init_wifi_task();
}
