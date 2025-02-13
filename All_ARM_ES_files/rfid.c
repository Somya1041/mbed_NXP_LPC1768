#include "rfid.h"

void rfid_init(void) {
	LPC_SC->PCONP |= (1 << 3);
	LPC_UART0->LCR = (1 << 7) | 3;
	LPC_UART0->DLM = 0;
	LPC_UART0->DLL = 78;
	LPC_UART0->LCR &= ~(1 << 7);
}

char rfid_read(void) {
	while (!(LPC_UART0->LSR & 1));
	return LPC_UART0->RBR;
}
