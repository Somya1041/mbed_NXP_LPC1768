#include <LPC17XX.h>

#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis);

int main(){
	uint32_t i, mid = 22;

    LPC_GPIO1->FIODIR |= ALL_LED;
    LPC_GPIO1->FIOCLR = ALL_LED;

    while (1) {
        for (i = 0; i <= (mid - 19); i++) {
            LPC_GPIO1->FIOSET = (1 << (19 + i)) | (1 << (26 - i));
            delay_ms(250);
        }

        delay_ms(150);

        for (i = 0; i <= (mid - 19); i++) {
            LPC_GPIO1->FIOCLR = (1 << (mid - i)) | (1 << (mid + i));
            delay_ms(250);
        }

        delay_ms(300);

        LPC_GPIO1->FIOCLR = ALL_LED;
        delay_ms(150);
    }
}

void delay_ms(uint32_t millis){
    uint32_t i, j;
    for (i = 0; i < millis; i++){
        for (j = 0; j < 1250; j++){}
    }
}
