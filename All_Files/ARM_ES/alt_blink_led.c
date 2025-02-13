//WAP to blink alternate leds.
#include <LPC17XX.h>
#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis);

int main(){
//configure P1.19 pin as output pin
	uint8_t i;
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;

	while(1){
	for(i = 19; i < 27; i++){
		LPC_GPIO1 -> FIOSET = (1 << i);
		delay_ms(400);
		LPC_GPIO1 -> FIOCLR = (1 << i);
	}
	}
}

void delay_ms(uint32_t millis){
uint32_t i, j;
for (i = 0; i < millis; i++){
for (j = 0; j < 1250; j++){}
}
}
