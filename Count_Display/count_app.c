# include "count.h"

int main(){
	int count = 0;
	char str_count[10];

	lcd_init();
	
	while(1){
		sprintf(str_count, "%02d", count);
		string_write(str_count);
		
		delay(100);
		count++;
		
		if(count == 100){
			count = 0;
		}
		
		cmd_reg(0x87);
	}
}
