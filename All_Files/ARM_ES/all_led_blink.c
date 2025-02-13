//WAP to blink all leds at sametime.
#include <LPC17XX.h>
#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis);

int main(){
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;

	while(1){ 
		LPC_GPIO1 -> FIOSET = ALL_LED;
		delay_ms(500);
		LPC_GPIO1 -> FIOCLR = ALL_LED;
		delay_ms(500);
	}
}

void delay_ms(uint32_t millis){
uint32_t i, j;
for (i = 0; i < millis; i++){
for (j = 0; j < 1250; i++){}
}
}
