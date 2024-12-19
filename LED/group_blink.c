//WAP to blink first 4 leds and then last 4 leds.
#include <LPC17XX.h>

#define ALL_LED (0xFF << 19)
#define GROUP1 (0x0F << 19)
#define GROUP2 (0x0F << 23)

void delay_ms(uint32_t millis);

int main(){
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;

	while(1){
		LPC_GPIO1 -> FIOSET = GROUP1;
		LPC_GPIO1 -> FIOCLR = GROUP2;

		delay_ms(400);
		
		LPC_GPIO1 -> FIOSET = GROUP2;
		LPC_GPIO1 -> FIOCLR = GROUP1;

		delay_ms(400);
	}
}

void delay_ms(uint32_t millis){
uint32_t i, j;
	for (i = 0; i < millis; i++){
		for (j = 0; j < 1250; j++){}
	}
}
           