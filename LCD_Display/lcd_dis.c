# include <LPC17xx.h>
# include <stdio.h>

#define RS (1 << 10)
#define EN (1 << 11)
#define DATA_PINS (0xFF << 15)

void delay(uint32_t ms){
	uint32_t i, j;
	for(i = 0; i < ms; i++){
		for(j = 0; j < 1250; j++){}
	}
}

void cmd_reg(char cmd){
	//SETTING DATA PINS AND CMD TO WRITE
	LPC_GPIO0 -> FIOCLR = DATA_PINS;
	LPC_GPIO0 -> FIOSET = cmd << 15;
	
	//MAKING RS 0 AND EN 1
	LPC_GPIO0 -> FIOCLR = RS;
	LPC_GPIO0 -> FIOSET = EN;
	
	delay(100);
	
	LPC_GPIO0 -> FIOCLR = EN; //RESETTING EN TO 0
}

void data_reg(char data){
	//SETTING DATA PINS AND CMD TO WRITE
	LPC_GPIO0 -> FIOCLR = DATA_PINS;
	LPC_GPIO0 -> FIOSET = data << 15;
	
	//MAKING RS 1 AND EN 1
	LPC_GPIO0 -> FIOSET = RS;
	LPC_GPIO0 -> FIOSET = EN;
	
	delay(100);
	
	LPC_GPIO0 -> FIOCLR = EN; //RESETTING EN TO 0
}

void string_write(char *str){
	while(*str != '\0'){
		data_reg(*str);
		str++;
	}
}

int main(){
	LPC_GPIO0 -> FIODIR |= RS;
	LPC_GPIO0 -> FIODIR |= EN;
	LPC_GPIO0 -> FIODIR |= DATA_PINS;
	
	cmd_reg(0x38); //8-bit mode write in 2 lines.
	cmd_reg(0x0E); //display on, cursor on.
	cmd_reg(0x01); //clear the screen
	
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
	
	delay(2000);
	
	cmd_reg(0xC0); //move cursor to second line
	
	string_write("SUNNY KR");	
	
	delay(3000);
	
	cmd_reg(0x01); //clear the screen
}
