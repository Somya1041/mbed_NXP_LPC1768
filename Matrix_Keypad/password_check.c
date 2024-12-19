# include <LPC17xx.h>
# include <string.h>
#include "lcd.h"

#define ROW_PINS (0x0F << 4) // P2.4 to P2.7 as rows
#define COL_PINS (0x0F) // P2.0 to P2.3 as columns

int main() {
    uint8_t row_codes[4] = {0x0E, 0x0D, 0x0B, 0x07}; // Row activation codes
    char key[4][4] = {
						{'0', '1', '2', '3'}, 
						{'4', '5', '6', '7'},
						{'8', '9', 'A', 'B'},
						{'C', 'D', 'E', 'F'}
					};

    char entered_password[5] = "";
    char correct_password[] = "1710";
    uint8_t password_index = 0;
    uint8_t i, j, col_val;

    LPC_GPIO2->FIODIR |= ROW_PINS;
    LPC_GPIO2->FIODIR &= ~COL_PINS;

    lcd_init();
    cmd_reg(0x0C);  // Display ON, cursor OFF
    string_write("Enter Password:");

    while (1) {
        for (i = 0; i < 4; i++) {
            LPC_GPIO2->FIOCLR = ROW_PINS; // Clear all row pins
            LPC_GPIO2->FIOSET = row_codes[i] << 4; // Set the current row active
            
            col_val = LPC_GPIO2->FIOPIN & COL_PINS; // Read column pins

            for (j = 0; j < 4; j++) {
                if (col_val == row_codes[j]) { // Match column value
                    break;
                }
            }

            if (col_val != 0x0F) { // A key is pressed
                if (password_index < 4) {
                    entered_password[password_index++] = keys[i][j];
                    data_reg(' ');
                }

                if (password_index == 4) {
                    entered_password[4] = '\0';

                    cmd_reg(0x01);

                    if (strcmp(entered_password, correct_password) == 0) {
                        string_write("Correct Password");
                    }
                    
                    else {
                        string_write("Wrong Password");
                    }

                    delay(3000);

                    cmd_reg(0x01);
                    
                    string_write("Enter Password:");
                    password_index = 0;
                }

                while ((LPC_GPIO2->FIOPIN & COL_PINS) != 0x0F); // Wait for key release
            }
        }
    }

    return 0;
}
