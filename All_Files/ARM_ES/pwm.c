#include "pwm.h"

void pwm_init(void) {
    LPC_SC->PCONP |= (1 << 6);             // Power on PWM1
    LPC_PINCON->PINSEL4 |= (1 << 0);       // Set P2.0 as PWM1.1
    LPC_PWM1->PCR |= (1 << 9);             // Enable PWM1.1 output
    LPC_PWM1->MR0 = 10000;                 // PWM period
    LPC_PWM1->MR1 = 0;                     // Initial duty cycle
    LPC_PWM1->LER |= (1 << 0) | (1 << 1);  // Load match registers
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);   // Enable counter and PWM
}

void pwm_open_gate(void) {
    LPC_PWM1->MR1 = 7000; // 70% duty cycle
    LPC_PWM1->LER |= (1 << 1);
}

void pwm_close_gate(void) {
    LPC_PWM1->MR1 = 0; // 0% duty cycle
    LPC_PWM1->LER |= (1 << 1);
}
