# include <LPC17xx.h>
#define ALL_LED (0xFF << 19)
#define LED1 (1 << 19)
#define LED2 (1 << 23)
#define LED3 (1 << 26)

int main(){
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;
	
	LPC_SC -> PCONP |= (1 << 1); //ENABLE POWER TO TIMER-0
	
	LPC_TIM0 -> PR = 0;
	
	LPC_TIM0 -> MR0 = 1000000; //DELAY = COUNT/PCLK = (PR+1)*(MR0)
	LPC_TIM0 -> MR1 = 5000000;
	LPC_TIM0 -> MR2 = 8000000;
	LPC_TIM0 -> MR3 = 10000000;
	
	LPC_TIM0 -> MCR = (1 << 10) | (1 << 9) | (1 << 6) | (1 << 3) | (1 << 0); //INTERRUPT AND REPEAT
	LPC_TIM0 -> TCR |= (1 << 1); //LOAD PC = 0
	LPC_TIM0 -> TCR |= (1 << 0); //START TIMER
	
	while(1){
		while((LPC_TIM0 -> IR & (1 << 0)) == 0){ }
		LPC_GPIO1 -> FIOSET = LED1;
		LPC_TIM0 -> IR |= (1 << 0);
		
		while((LPC_TIM0 -> IR & (1 << 1)) == 0){ }
		LPC_GPIO1 -> FIOSET = LED2;
		LPC_TIM0 -> IR |= (1 << 1);
		
		while((LPC_TIM0 -> IR & (1 << 2)) == 0){ }
		LPC_GPIO1 -> FIOSET = LED3;
		LPC_TIM0 -> IR |= (1 << 2);
		
		while((LPC_TIM0 -> IR & (1 << 3)) == 0){ }
		LPC_GPIO1 -> FIOSET = ALL_LED;
		LPC_TIM0 -> IR |= (1 << 3);
	}
}
