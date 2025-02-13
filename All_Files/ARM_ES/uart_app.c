# include "uart0.h"

int main(){
	char sval[20];
	char ch = 'A';
	char str[] = "Sunny";
	float cgpa = 8.89;
	
	uart0_init();
	
	uart0_byte_transmit(ch);
	new_line();
	delay(1000);
	
	uart0_str_transmit(str);
	new_line();
	delay(1000);
	
	sprintf(sval, "%.2f", cgpa);
	uart0_str_transmit(sval);
	new_line();
	delay(1000);
}
