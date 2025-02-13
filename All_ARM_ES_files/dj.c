#include <LPC17xx.h>
#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis);

int main(void)
{
    uint32_t i;

    LPC_GPIO1->FIODIR |= ALL_LED;
    LPC_GPIO1->FIOCLR = ALL_LED;

    while (1){ 
        for (i = 19; i <= 26; i++) {
            LPC_GPIO1->FIOSET = (1 << i);
            delay_ms(100);
            LPC_GPIO1->FIOCLR = (1 << i);
        }

        for (i = 26; i >= 19; i--) {
            LPC_GPIO1->FIOSET = (1 << i);
            delay_ms(100);                
            LPC_GPIO1->FIOCLR = (1 << i);
        }

        for (i = 0; i < 5; i++) {
            LPC_GPIO1->FIOSET = ALL_LED; 
            delay_ms(50);              
            LPC_GPIO1->FIOCLR = ALL_LED; 
            delay_ms(50);
        }

        for (i = 19; i <= 26; i += 2) {
            LPC_GPIO1->FIOSET = (1 << i);
        }

        delay_ms(50);
        LPC_GPIO1->FIOCLR = ALL_LED;

        for (i = 20; i <= 26; i += 2) {
            LPC_GPIO1->FIOSET = (1 << i);
        }

        delay_ms(50);
        LPC_GPIO1->FIOCLR = ALL_LED;

        for (i = 19; i <= 25; i++) {
            LPC_GPIO1->FIOSET = (1 << i) | (1 << (i + 1));
            delay_ms(50);                                
            LPC_GPIO1->FIOCLR = (1 << i) | (1 << (i + 1));
        }

        for (i = 19; i <= 26; i++) {
            LPC_GPIO1->FIOSET = (1 << i);
            delay_ms(50);
        }

        delay_ms(200);

        for (i = 26; i >= 19; i--) {
            LPC_GPIO1->FIOCLR = (1 << i);
            delay_ms(50);
        }
    }
}

void delay_ms(uint32_t millis)
{
    uint32_t i, j;
    for (i = 0; i < millis; i++) {
        for (j = 0; j < 1250; j++) {
        }
    }
}
