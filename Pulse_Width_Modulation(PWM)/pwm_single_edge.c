# include <LPC17xx.h>
# include "lcd.h"

int main(){
	LPC_SC -> PCONP |= (1 << 6); //POWER ON PWM1
	
	LPC_PINCON -> PINSEL3 |= (1 << 9);
	LPC_PINCON -> PINSEL3 &= ~(1 << 8);
	
	LPC_PWM1 -> PCR |= (1 << 10); //EMABLE PWM1.2 TO GIVE OUTPUT
	LPC_PWM1 -> PCR &= ~(1 << 2); //SINGLE EDGE MODE FOR PWM1.2
	
	LPC_PWM1 -> PR = 0;
	
	LPC_PWM1 -> MCR |= (1 << 1); //REPEAT COUNT ON MR0 MATCH
	
	LPC_PWM1 -> MR0 = 10000; //PWM SINGAL FREQ 100Hz
	LPC_PWM1 -> MR2 = 2000; //20% DUTY CYCLE
	LPC_PWM1 -> LER |= (1 << 2) | (1 << 0); //LOAD ENABLE FOR MR2 & MR0
	
	LPC_PWM1 -> TCR |= (1 << 3) | (1 << 0); //0 FOR ENABLE COUNTER & 3 FOR ENABLE PWM
	
	while(1){
		//20% duty cycle
		LPC_PWM1 -> MR2 = 2000;
		LPC_PWM1 -> LER = (1 << 2);
		delay(400);
		
		//40% duty cycle
		LPC_PWM1 -> MR2 = 2000;
		LPC_PWM1 -> LER = (1 << 2);
		delay(400);
		
		//60% duty cycle
		LPC_PWM1 -> MR2 = 6000;
		LPC_PWM1 -> LER = (1 << 2);
		delay(400);
		
		//80% duty cycle
		LPC_PWM1 -> MR2 = 8000;
		LPC_PWM1 -> LER = (1 << 2);
		delay(400);
	}
}
