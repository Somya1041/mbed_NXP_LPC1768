#include "uart.h"

void uart0_init(void) {
	LPC_SC->PCONP |= (1 << 3);

	LPC_PINCON->PINSEL0 |= (1 << 4);
	LPC_PINCON->PINSEL0 &= ~(1 << 5);

	LPC_PINCON->PINSEL0 |= (1 << 6);
	LPC_PINCON->PINSEL0 &= ~(1 << 7);

	LPC_UART0->LCR |= (1 << 1) | (1 << 0);
	LPC_UART0->LCR &= ~(1 << 2);
	LPC_UART0->LCR &= ~(1 << 3);

	LPC_UART0->LCR |= (1 << 7);
	LPC_UART0->DLM = 0;
	LPC_UART0->DLL = 6;
	LPC_UART0->FDR |= (0x0C << 4) | (1 << 0);
	LPC_UART0->LCR &= ~(1 << 7);
}

void uart0_byte_transmit(char byte) {
	LPC_UART0->THR = byte;
	while ((LPC_UART0->LSR & (1 << 5)) == 0);
}

char uart0_byte_receive(void) {
	while ((LPC_UART0->LSR & (1 << 0)) == 0);
	return LPC_UART0->RBR;
}

void uart0_str_transmit(char *str) {
	while (*str != '\0') {
		uart0_byte_transmit(*str);
		str++;
	}
}

//void delay_ms(uint32_t ms) {
//	uint32_t i, j;
//	for (i = 0; i < ms; i++)
//		for (j = 0; j < 1250; j++);
//}

void new_line(void) {
	uart0_byte_transmit('\r');
	uart0_byte_transmit('\n');
}
