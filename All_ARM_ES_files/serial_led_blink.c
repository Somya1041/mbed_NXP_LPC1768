//WAP to blink led.
#include <LPC17XX.h>
#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis);

int main(){
//configure P1.19 pin as output pin
	uint32_t i;
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;

	while(1){
	for(i = 19; i <= 26; i++){
		LPC_GPIO1 -> FIOSET = (i << 1);
		delay_ms(50);
		LPC_GPIO1 -> FIOCLR = (i << 1);
	}
	}
}

void delay_ms(uint32_t millis){
uint32_t i, j;
for (i = 0; i < millis; i++){
for (j = 0; j < 1250; i++){}
}
}
