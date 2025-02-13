# include <LPC17xx.h>
# include "lcd.h"
#define ALL_LED (0xFF << 19)
#define BUZZER (1 << 27)

int main(){
	LPC_GPIO1 -> FIODIR |= ALL_LED;
	LPC_GPIO1 -> FIODIR |= BUZZER;
	
	LPC_GPIO1 -> FIOCLR = ALL_LED;
	LPC_GPIO1 -> FIOCLR = BUZZER;

	LPC_WDT -> WDMOD |= (1 << 1) | (1 << 0); //ENABLE AND RESET ON on TIME-OUT
	LPC_WDT -> WDCLKSEL &= ~0x03; //SELECT INTERNAL RC OSCILLATOR FOR CLK
	LPC_WDT -> WDTC = 4000000; //DELAY = COUNT*CLK = 4000000 * (0.25u*4) = 4sec
	LPC_WDT -> WDFEED = 0xAA; //WRITE FEED SEQUENCE TO START WDT
	LPC_WDT -> WDFEED = 0x55;
	
	LPC_GPIO1 -> FIOSET = BUZZER;
	delay(100);
	LPC_GPIO1 -> FIOCLR = BUZZER;
	
	while(1){
		LPC_GPIO1 -> FIOSET = ALL_LED;
		delay(500);
		
		LPC_GPIO1 -> FIOCLR = ALL_LED;
		delay(500);
		//while(1);

		//RELOADING WDT IN 4sec
		LPC_WDT -> WDFEED = 0xAA; //reload WDT before time-out
		LPC_WDT -> WDFEED = 0x55;
	}
}
