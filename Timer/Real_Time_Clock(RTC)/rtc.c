# include <LPC17xx.h>
# include "lcd.h"

int main(){
	char stime[16];
	char sdate[16];
	
	lcd_init();

	cmd_reg(0x0C);
	
	LPC_SC -> PCONP |= (1 << 9); //ENABLE POWER to RTC
	
	LPC_RTC -> CCR = 0x00; //DISABLE TIME COUNTERS
	
	LPC_RTC -> HOUR = 11;
	LPC_RTC -> MIN = 31;
	LPC_RTC -> SEC = 0;
	
	LPC_RTC -> DOM = 14;
	LPC_RTC -> MONTH = 12;
	LPC_RTC -> YEAR = 2024;
	
	LPC_RTC -> CCR = 0x01; //ENABLE TIME COUNTERS
	
	while(1){
		sprintf(stime, "%02d:%02d:%02d", LPC_RTC->HOUR, LPC_RTC->MIN, LPC_RTC->SEC);
		string_write(stime);

		cmd_reg(0xC0);
		
		sprintf(sdate, "%02d/%02d/%04d", LPC_RTC->DOM, LPC_RTC->MONTH, LPC_RTC->YEAR);
		string_write(sdate);
		
		cmd_reg(0x80);
	}
}
