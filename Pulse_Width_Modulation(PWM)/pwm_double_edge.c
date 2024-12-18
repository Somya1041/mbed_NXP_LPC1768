# include <LPC17xx.h>
# include <stdint.h>
# include "lcd.h"

int main(){
	LPC_SC -> PCONP |= (1 << 6); //POWER ON PWM1
	
	LPC_PINCON -> PINSEL3 |= (1 << 9); //SELECT ALTERNATE POWER-ON PWM1 P1.20
	LPC_PINCON -> PINSEL3 &= ~(1 << 8);

	LPC_PWM1 -> PCR |= (1 << 10); //ENABLE PWM1.2 channel output
	LPC_PWM1 -> PCR |= (1 << 2); //SELECT DOUBLE EDGE mode for PWM1.2 channel2

	LPC_PWM1 -> PR = 0;

	LPC_PWM1 -> MCR |= (1 << 1); //REPEAT COUNT ON MR0 MATCH 

	LPC_PWM1 -> MR0 = 10000; //PWM SIGNAL FREQ 100 HZ
	LPC_PWM1 -> MR1 = 2000; //SIGNAL SET-TIME
	LPC_PWM1 -> MR2 = 4000; //SIGNAL RESET-TIME; 20% DUTY CYCLE
	LPC_PWM1 -> LER |= (1 << 2) | (1 << 1) | (1 << 0); //LOAD ENABLE FOR MR2, MR1 & MR0

	LPC_PWM1 -> TCR |= (1 << 3) | (1 << 0);	//LOAD PC = 0 AND TC = 0 AND ENABLE COUNTER; SELECT PWM TIMER REGISTER ENABLE

	while(1){
		//20% duty cycle
		LPC_PWM1 -> MR1 = 2000; //Rising Edge
		LPC_PWM1 -> MR2 = 4000; //Falling Edge
		LPC_PWM1 -> LER |= (1 << 1) | (1 << 2);
		delay(500);

		//40% duty cycle
		LPC_PWM1 -> MR1 = 2000;
		LPC_PWM1 -> MR2 = 6000;
		LPC_PWM1 -> LER |= (1 << 1) | (1 << 2);
		delay(500);

		//60% duty cycle
		LPC_PWM1 -> MR1 = 2000;
		LPC_PWM1 -> MR2 = 8000;
		LPC_PWM1 -> LER |= (1 << 1) | (1 << 2);
		delay(500);

		//70% duty cycle
		LPC_PWM1 -> MR1 = 2000;  
		LPC_PWM1 -> MR2 = 9000;
		LPC_PWM1 -> LER |= (1 << 1) | (1 << 2);
		delay(500);
	}
}
