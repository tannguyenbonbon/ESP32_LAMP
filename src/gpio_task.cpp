#include <Arduino.h>
#include "interrupt_task.h"
#include "pin_config.h"

static void init_relay_gpio()
{
    pinMode(RELAY_PIN, OUTPUT);
    control_relay(LOW);         //TURN OFF RELAY
}

static void init_builtin_led_gpio()
{
    pinMode(TIMER_LED_PIN, OUTPUT);
    digitalWrite(TIMER_LED_PIN, LOW);
}

void init_gpio()
{
    init_builtin_led_gpio();
    init_relay_gpio();
}

