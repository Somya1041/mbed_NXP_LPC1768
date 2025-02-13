#include <LPC17xx.h>
#include <stdio.h>
#include <string.h> 
#include "lcd_proj.c"
#include "toll_gate.c"

int main(){
	LPC_GPIO1 -> FIODIR |= (0xff<<19) | (1<<27);
    lcd_config();  // Initialize LCD
    uart_init();   // Initialize UART     547bd23  17920966
	key_main_prog();
}
