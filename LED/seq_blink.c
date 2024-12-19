# include <LPC17xx.h>

#define ALL_LED (0xFF << 19)

void delay_ms(uint32_t millis){
	uint32_t i, j;
	for(i = 0; i < millis; i++){
		for(j = 0; j < 1250; j++){}
	}
}

int main(){
	uint32_t i;
	
	LPC_GPIO1->FIODIR |= ALL_LED;
	LPC_GPIO0->FIOCLR = ALL_LED;

	while(1){
		for(i = 19; i <= 26; i++){
			LPC_GPIO1->FIOSET = (1 << i);
			delay_ms(150);
		}

		LPC_GPIO1 -> FIOCLR |= ALL_LED;
		delay_ms(150);

		for(i = 26; i >= 19; i--){
			LPC_GPIO1->FIOSET = (1 << i);
			delay_ms(150);
		}

		LPC_GPIO1->FIOCLR = ALL_LED;
		delay_ms(400);

	}
}
