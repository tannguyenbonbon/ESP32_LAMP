#include <WiFi.h>
#include <WiFiClient.h>

#include "serial_log.h"
#include "project_info.h"

const char *SSID = "CENTRAL SPACE 69L1B";
const char *PASSWORD = "central69";

extern EventGroupHandle_t event_group = NULL;

static void WiFi_Task(void *pvParameters)
{
    SERIAL_LOG("Connecting to Wi-Fi: %s\n", SSID);
    WiFi.begin(SSID, PASSWORD);

    unsigned long startAttemptTime = millis();
    const unsigned long connectionTimeout = 10000; // Thời gian chờ kết nối Wi-Fi (10 giây)

    while (true)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            SERIAL_LOG("\nConnected to WiFi\n");
            // Xóa bit NOT_CONNECTED và đặt bit CONNECTED
            xEventGroupClearBits(event_group, WIFI_DISCONNECTED_BIT);
            xEventGroupSetBits(event_group, WIFI_CONNECTED_BIT);
            break;
        }

        if (millis() - startAttemptTime > connectionTimeout)
        {
            SERIAL_LOG("Failed to connect to WiFi. Retrying in 30 seconds...\n");
            // Đặt bit NOT_CONNECTED
            xEventGroupSetBits(event_group, WIFI_DISCONNECTED_BIT);
            vTaskDelay(pdMS_TO_TICKS(30000)); // Đợi 30 giây trước khi thử lại
            startAttemptTime = millis();      // Đặt lại thời gian chờ
            WiFi.begin(SSID, PASSWORD);       // Thử kết nối lại
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // Đợi 500ms trước khi kiểm tra lại
        SERIAL_LOG(".");
    }
}

void wifi_init()
{
    xTaskCreate(WiFi_Task, "WiFi_Task", 4096, NULL, 1, NULL);
}