# include <LPC17xx.h>

#define ALL_LED (0xFF << 19)

int main(){
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIOCLR = ALL_LED;
	
	LPC_SC -> PCONP |= (1 << 1); //ENABLE POWER TO TIMER-0
	
	LPC_TIM0 -> PR = 0x00;
	LPC_TIM0 -> MR0 = 2000000; //DELAY = COUNT/PCLK = (PR+1)*(MR0)
	LPC_TIM0 -> MCR = (1 << 1) | (1 << 0); //INTERRUPT AND REPEAT
	LPC_TIM0 -> TCR |= (1 << 1); //LOAD PC = 0
	LPC_TIM0 -> TCR |= (1 << 0); //START TIMER
	
	while(1){
		LPC_GPIO1 -> FIOSET = ALL_LED;
		while((LPC_TIM0 -> IR & (1 << 0)) == 0){ }
		
		LPC_TIM0 -> IR |= (1 << 0);
		
		LPC_GPIO1 -> FIOCLR = ALL_LED;
		while((LPC_TIM0 -> IR & (1 << 0)) == 0){ }
		
		LPC_GPIO1 -> FIOCLR = ALL_LED;
	}
}
