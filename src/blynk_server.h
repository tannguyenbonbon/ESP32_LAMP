#pragma once


#ifndef BLYNK_SERVER_H
#define BLYNK_SERVER_H

#define BLYNK_TEMPLATE_ID "TMPL6kvCPkity"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "dgV-VB9RIrD3GcKUtXcZ44UJKzHayFOP"

void sync_VirtualPin(int PIN, int status);
void start_blynk_server();

#endif  //BLYNK_SERVER_H