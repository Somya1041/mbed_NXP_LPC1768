# include <LPC17xx.h>
# include <stdint.h>
#define BUZZER (1 << 27)
#define SW1 (1 << 11)
#define SW2 (1 << 12)
#define ALL_LED (0xFF << 19)

void delay(uint32_t ms){
uint32_t i, j;
	for(i = 0; i < ms; i++){
		for(j = 0; j < 1250; j++){}
}
}

int main(){
	LPC_GPIO1 -> FIODIR |= BUZZER; 
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO2 -> FIODIR &= ~SW1;
	LPC_GPIO2 -> FIODIR &= ~SW2;
	LPC_GPIO1 -> FIOCLR = ALL_LED;
	LPC_GPIO1 -> FIOCLR = BUZZER;
	
	while(1){
		if ((LPC_GPIO2 -> FIOPIN & SW1) != 0){
			LPC_GPIO1 -> FIOSET = BUZZER;
		}
		
		else{
			LPC_GPIO1 -> FIOCLR = BUZZER;
		}
		
		if ((LPC_GPIO2 -> FIOPIN & SW2) != 0){
			LPC_GPIO1 -> FIOSET = ALL_LED;
		}
		
		else{
			LPC_GPIO1 -> FIOCLR = ALL_LED;
		}
	}
}
