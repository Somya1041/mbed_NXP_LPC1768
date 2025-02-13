#include "motor.h"

// System Clock Initialization
void SystemInit(void) {
    LPC_SC->PLL0CON = 0;        // Disable PLL0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    
    LPC_SC->SCS |= (1 << 5);    // Enable main oscillator
    while (!(LPC_SC->SCS & (1 << 6))); // Wait for oscillator to stabilize

    LPC_SC->CLKSRCSEL = 1;      // Select main oscillator as clock source
    LPC_SC->PLL0CFG = (25 << 0) | (2 << 16); // M = 25, N = 2
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    LPC_SC->PLL0CON = 1;        // Enable PLL0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    while (!(LPC_SC->PLL0STAT & (1 << 26))); // Wait for PLL to lock

    LPC_SC->CCLKCFG = 3;        // Divide by 4 for 100MHz CPU clock
    LPC_SC->PLL0CON = 3;        // Connect PLL
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    LPC_SC->PCLKSEL0 = 0xAAAAAAAA; // Peripheral clock divider
    LPC_SC->PCLKSEL1 = 0xAAAAAAAA;
}

// PWM1.1 Initialization on P1.18
void PWM1_Init(void) {
    LPC_SC->PCONP |= (1 << 6);         // Power on PWM1 module
    LPC_PINCON->PINSEL3 |= (1 << 4);   // Set P1.18 as PWM1.1 (Function 01)
    
    LPC_PWM1->PR = 0;                  // No prescaler
    LPC_PWM1->MCR = (1 << 1);          // Reset TC on match (PWM cycle)
    LPC_PWM1->MR0 = 20000;             // 20ms period (for 50Hz servo PWM)
    LPC_PWM1->MR1 = 1500;              // Default: 1.5ms pulse width (90-degree position)
    
    LPC_PWM1->LER |= (1 << 0) | (1 << 1); // Enable PWM match updates
    LPC_PWM1->PCR |= (1 << 9);         // Enable PWM1.1 output
    LPC_PWM1->TCR = (1 << 0) | (1 << 3); // Enable PWM and Counter
}

// Function to set servo angle (0° to 180°)
void SetServoAngle(float angle) {
    uint32_t pulseWidth = 1000 + (angle / 180.0) * 1000; // Convert 0°-180° to 1ms-2ms
    LPC_PWM1->MR1 = pulseWidth;
    LPC_PWM1->LER |= (1 << 1);  // Update match register
}
