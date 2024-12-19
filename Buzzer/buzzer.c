# include <LPC17xx.h>

#define BUZZER (0x01 << 27)

void delay_ms(uint32_t mls){
	uint32_t i, j;
	for (i = 0; i < mls; i++){
		for (j = 0; j < 1250; j++){}
	}
}

int main(){
	LPC_GPIO1 -> FIODIR |= BUZZER;
	LPC_GPIO1 -> FIOCLR = BUZZER;

	while(1){
		LPC_GPIO1 -> FIOSET = BUZZER;
		delay_ms(250);
			
		LPC_GPIO1 -> FIOCLR = BUZZER;
		delay_ms(250);
	}
}
