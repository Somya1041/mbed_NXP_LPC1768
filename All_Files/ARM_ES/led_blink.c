//WAP to blink led.
#include <LPC17xx.h>
#define LED1 (0x01 << 19)

int main(){
	int i;

	LPC_GPIO1 -> FIODIR |= LED1;

	while(1){
		LPC_GPIO1 -> FIOSET = LED1;
		for(i = 0; i < 100; i++) {}
		
		LPC_GPIO1 -> FIOCLR = LED1;
		for(i = 0; i < 100; i++) {}
	}
}
