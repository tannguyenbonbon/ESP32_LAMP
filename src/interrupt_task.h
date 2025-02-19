#pragma once

#ifndef INTERRUPT_TASK_H_
#define INTERRUPT_TASK_H

void enable_interrupt(int interrupt_pin);
void disable_interrupt(int interrupt_pin);

void start_relay_control();
void control_relay(bool status);

#endif //INTERRUPT_TASK_H