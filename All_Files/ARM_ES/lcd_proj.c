#include "lcd_proj.h"

void lcd_config(void)
{
  LPC_GPIO0 -> FIODIR |= LCD_DATA_PINS;
  LPC_GPIO0 -> FIODIR |= LCD_RS_PIN(10);
  LPC_GPIO0 -> FIODIR |= LCD_EN_PIN(11);
  lcd_cmd_write(0X38);
  lcd_cmd_write(0X0E);
  lcd_cmd_write(0X01);
  return;
}

void lcd_cmd_write(char cmd)
{
  LPC_GPIO0 -> FIOCLR |= LCD_DATA_PINS;  
  LPC_GPIO0 -> FIOSET |= cmd << 15;
  LPC_GPIO0 -> FIOCLR |= LCD_RS_PIN(10);
  LPC_GPIO0 -> FIOSET |= LCD_EN_PIN(11);
  delay(100);
  LPC_GPIO0 -> FIOCLR |= LCD_EN_PIN(11);
  return;
}

void lcd_data_write(char data)
{
  LPC_GPIO0 -> FIOCLR |= LCD_DATA_PINS;  
  LPC_GPIO0 -> FIOSET |= data << 15;
  LPC_GPIO0 -> FIOSET |= LCD_RS_PIN(10);
  LPC_GPIO0 -> FIOSET |= LCD_EN_PIN(11);
  delay(100);
  LPC_GPIO0 -> FIOCLR |= LCD_EN_PIN(11);
  return;
}

void lcd_str_write(char *str)
{
  while(*str)
  {
   lcd_data_write(*str);
   str++;
  }
}                      

void lcd_num(unsigned int num)
{

  if(num)
  {
    lcd_num(num/10);
         lcd_num(num%10+0X30);
  }
}

void delay(unsigned int a)
{
  int i,j;
  for(i=0;i<a;i++)
  for(j=0;j<2000;j++);
}
