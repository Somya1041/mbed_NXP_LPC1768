# include <LPC17xx.h>
# include <stdio.h>

#define RS (1 << 10)
#define EN (1 << 11)
#define DATA_PINS (0xFF << 15)

void delay(uint32_t ms);
void cmd_reg(char cmd);
void data_reg(char data);
void string_write(char *str);
void lcd_init(void);
