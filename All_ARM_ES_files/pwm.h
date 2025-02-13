#ifndef PWM_H
#define PWM_H

#include <LPC17xx.h>
#include <stdint.h>

void pwm_init(void);
void pwm_open_gate(void);
void pwm_close_gate(void);

#endif // PWM_H
