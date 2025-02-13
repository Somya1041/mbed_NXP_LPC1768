#ifndef SERVO_H
#define SERVO_H

#include<LPC17xx.h>

void SystemInit(void);
void PWM1_Init(void);
void SetServoAngle(float angle);

#endif
