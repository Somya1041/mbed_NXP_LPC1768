# include <LPC17xx.h>
# include "lcd.h"

int main(){
	char ch = 'A';

	LPC_SC -> PCONP |= (1 << 3); //POWER ON UART0 MODULE
	
	LPC_PINCON -> PINSEL0 |= (1 << 4); //SELECT P0.2 PIN FOR TXD
	LPC_PINCON -> PINSEL0 &= ~(1 << 5); 
		
	LPC_PINCON -> PINSEL0 |= (1 << 6); //SELECT P0.3 PIN FOR R	XD
	LPC_PINCON -> PINSEL0 &= ~(1 << 7); 
	
	LPC_UART0 -> LCR |= (1 << 1) | (1 << 0); //DATA LENGTH = 8BITS
	LPC_UART0 -> LCR &= ~(1 << 2); //SINGLE STOP BIT
	LPC_UART0 -> LCR &= ~(1 << 3); //NO PARITY BIT
	
	LPC_UART0 -> LCR |= (1 << 7); //DIVISOR LATCH ENABLE
	LPC_UART0 -> DLM = 0;
	LPC_UART0 -> DLL = 6; //BAUD-RATE = PCLK/16*DL = 1000000/16* (256*DLM + DLL) = 1000000/(16*6) = 10400
	LPC_UART0 -> FDR |= (0x0C << 4) | (1 << 0); //BR = PCLK/16*DL(1+D/M) = 1000000/16* (256*DLM+DLL) (1+D/M) = 1000000/(16*6*(1+1/12)) = 9615
	LPC_UART0 -> LCR &= ~(1 << 7); //DISABLED LATCH
	
	//LPC_UART0 -> THR = 'A'; //TRANSMITTING VALUE 'A'
	
	//while((LPC_UART0 -> LSR & (1 << 5)) == 0){} //WAIT FOR DATA TRANSMISSION TO COMPLETE
	
	while(ch <= 'Z') {                   
        LPC_UART0 -> THR = ch; // Send character
        while((LPC_UART0 -> LSR & (1 << 5)) == 0); // Wait for data transmission to complete
		delay(1000); // Add delay
        ch++; // Increment the character
    }
    
    while(1); 
}