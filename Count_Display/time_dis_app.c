# include "count.h"

int main(){
	int hr = 12, min = 59, sec = 58;
	char str_time[10];
	
	lcd_init();
	
	while(1){
		cmd_reg(0x84);

		sprintf(str_time, "%02d:%02d:%02d", hr, min, sec);
		string_write(str_time);

		delay(1000);
		
		sec = sec + 1;
		
		if(sec == 60){
			sec = 0;
			min = min + 1;
		}
		
		if(min == 60){
			min = 0;
			hr = hr + 1;
		}
		
		if(hr == 24){
			hr = 0;
		}
	}
}
