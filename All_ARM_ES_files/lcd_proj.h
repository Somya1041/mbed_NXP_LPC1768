#include <LPC17XX.h>
#include <stdint.h>

#define LCD_DATA_PINS (0XFF<<15)
#define LCD_RS_PIN(X) (1<<X)
#define LCD_EN_PIN(X) (1<<X)

void lcd_config(void);
void lcd_cmd_write(char);
void lcd_data_write(char);
void lcd_str_write(char *);
void lcd_num(unsigned int num);
void delay(unsigned int a);
