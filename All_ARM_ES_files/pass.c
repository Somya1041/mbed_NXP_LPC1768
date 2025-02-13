# include <LPC17xx.h>
# include <string.h>
#include "lcd.h"
#define ROW_PINS (0x0F << 4)  // P2.4 to P2.7 as rows
#define COL_PINS (0x0F)       // P2.0 to P2.3 as columns

int main() {
    uint8_t row_codes[4] = {0x0E, 0x0D, 0x0B, 0x07};  // Row activation codes
    char keys[4][4] = {
        {'0', '1', '2', '3'},
        {'4', '5', '6', '7'},
        {'8', '9', 'A', 'B'},
        {'C', 'D', 'E', 'F'}
    };

    char entered_password[5] = "";  // Array to store entered password
    char correct_password[] = "1710";  // Predefined correct password
    uint8_t password_index = 0;    // Index to track password input
    uint8_t i, j, col_val;

    // Configure GPIO pins
    LPC_GPIO2->FIODIR |= ROW_PINS;  // Set row pins as output
    LPC_GPIO2->FIODIR &= ~COL_PINS; // Set column pins as input

    // Initialize LCD
    lcd_init();
    cmd_reg(0x0C);  // Display ON, cursor OFF
    string_write("Enter Password:");

    while (1) {
        for (i = 0; i < 4; i++) {
            LPC_GPIO2->FIOCLR = ROW_PINS;             // Clear all row pins
            LPC_GPIO2->FIOSET = row_codes[i] << 4;    // Set the current row active
            
            col_val = LPC_GPIO2->FIOPIN & COL_PINS;   // Read column pins

            for (j = 0; j < 4; j++) {
                if (col_val == row_codes[j]) {       // Match column value
                    break;
                }
            }

            if (col_val != 0x0F) {                   // A key is pressed
                if (password_index < 4) {           // Limit password to 4 characters
                    entered_password[password_index++] = keys[i][j];
                    data_reg(' ');             // Display '' for entered characters
                }

                if (password_index == 4) {          // When 4 characters are entered
                    entered_password[4] = '\0';     // Null-terminate the password string

                    cmd_reg(0x01);            // Clear the screen
                    if (strcmp(entered_password, correct_password) == 0) {
                        string_write("Correct Password");
                    } else {
                        string_write("Wrong Password");
                    }

                    delay(3000);                 // Delay to show result
                    cmd_reg(0x01);            // Clear the screen for next input
                    string_write("Enter Password:");
                    password_index = 0;             // Reset index for new input
                }

                while ((LPC_GPIO2->FIOPIN & COL_PINS) != 0x0F);  // Wait for key release
            }
        }
    }

    return 0;  // Return from main
}
