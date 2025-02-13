#ifndef UART_H
#define UART_H

#include <LPC17xx.h>
#include <stdio.h>

void uart0_init(void);
void uart0_byte_transmit(char byte);
char uart0_byte_receive(void);
void uart0_str_transmit(char *str);
//void delay_ms(uint32_t ms);
void new_line(void);

#endif
