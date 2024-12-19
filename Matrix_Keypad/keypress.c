# include <LPC17xx.h>
# include "lcd.h"

#define ROW_PINS (0x0F << 4)
#define COL_PINS (0x0F)

int main(){
	uint8_t code[4] = {0x0E, 0x0D, 0x0B, 0x07};
	char key[4][4] = {
						{'0', '1', '2', '3'}, 
						{'4', '5', '6', '7'},
						{'8', '9', 'A', 'B'},
						{'C', 'D', 'E', 'F'}
					};
	uint8_t i, j, col_val;
	
	LPC_GPIO2 -> FIODIR |= ROW_PINS; //MAKE ROW_PINS AS OUTPUT PINS
	LPC_GPIO2 -> FIODIR &= ~COL_PINS; //MAKE COL_PINS AS INPUT PINS
	
	lcd_init();
	cmd_reg(0x0C);
	string_write("Key Pressed: ");
	
	while(1){
		for(i = 0; i < 4; i++){
			LPC_GPIO2 -> FIOCLR = ROW_PINS; //MAKE ROW_PINS AS 0 for output
			LPC_GPIO2 -> FIOSET = code[i] << 4; //MAKE COL_PINS AS INPUT PINS
			
			col_val = LPC_GPIO2 -> FIOPIN & 0x0F; //GET ALL 1s OF KEYPAD
			
			for(j = 0; j < 4; j++){
				if(col_val == code[j]){
					break;
				}
			}
			
			if(col_val != 0x0F){
				data_reg(key[i][j]);
				cmd_reg(0x10);
			}
		}
	}
}
