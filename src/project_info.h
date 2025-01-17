#pragma once

#ifndef PROJECT_INFO_H_
#define PROJECT_INFO_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#define WIFI_CONNECTED_BIT              BIT0
#define WIFI_DISCONNECTED_BIT           BIT1

#define BLYNK_SERVER_CONNECTED_BIT      BIT2

#define INTERRUPT_FLAG_ENABLE_BIT       BIT3


#endif //PROJECT_INFO_H_