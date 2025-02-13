# include <LPC17xx.h>
# include "lcd.h"

#define BUZZER (1 << 27)

int main(){
	LPC_GPIO1 -> FIODIR |= BUZZER;
	LPC_GPIO1 -> FIOCLR = BUZZER;
	
	lcd_init();
	cmd_reg(0x0C);
	
	LPC_SC -> PCONP |= (1 << 9); //ENABLE POWER to RTC
	
	LPC_RTC -> CCR = 0x00; //DISABLE TIME COUNTERS
	
	LPC_RTC -> HOUR = 23;
	LPC_RTC -> MIN = 59;
	LPC_RTC -> SEC = 55;
	
	LPC_RTC -> DOM = 31;
	LPC_RTC -> MONTH = 12;
	LPC_RTC -> YEAR = 2024;
	
	LPC_RTC -> ALHOUR = 00;
	LPC_RTC -> ALMIN = 00;
	
	LPC_RTC -> AMR = 0xF9; //ENABLE ONLY HOUR AND MIN FOR COMPARISON
	
	LPC_RTC -> CCR = 0x01; //ENABLE TIME COUNTERS
	
	while(1){
		if((LPC_RTC -> ILR & (1 << 1)) != 0){ //IF CURRENT TIME == ALARM TIME
			LPC_RTC -> ILR |= (1 << 1); //CLEAR ALARM INTERRUPT
			LPC_GPIO1 -> FIOSET = BUZZER;
			string_write("HAPPY NEW YEAR!");
			cmd_reg(0x01);
		}
		
		else{
			LPC_GPIO1 -> FIOCLR = BUZZER;
		}
	}
}
