#include "blynk_server.h"
#include <BlynkSimpleEsp32.h>
#include "relay_control.h"

extern EventGroupHandle_t event_group;

void syncVirtualPin(int PIN, int status) 
{
  Blynk.virtualWrite(PIN, status);
}


BLYNK_WRITE(V0) {
    int pinValue = param.asInt();
    // relay_status = pinValue ? true:false;
    // control_relay(relay_status);
}