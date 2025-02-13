# include "lcd.h"

int main(){
	LPC_GPIO0 -> FIODIR |= RS;
	LPC_GPIO0 -> FIODIR |= EN;
	LPC_GPIO0 -> FIODIR |= DATA_PINS;
	
	cmd_reg(0x38); //8-bit mode write in 2 lines.
	cmd_reg(0x0E); //display on, cursor on.
	cmd_reg(0x01); //clear the screen
	/*
	data_reg(0x53);
	data_reg('O'); 
	data_reg('M'); 
	data_reg('Y'); 
	data_reg(0x41); 
	data_reg(' ');
	data_reg(0x41);
	data_reg('N');
	data_reg(0x41);
	data_reg('N');
	data_reg('D');
	*/
	string_write("SOMYA ANAND");
	
	delay(2000);
	
	cmd_reg(0xC0); //move cursor to second line
	
	string_write("SUNNY KR");	
	
	delay(2000);
	
	cmd_reg(0x01); //clear the screen
}
