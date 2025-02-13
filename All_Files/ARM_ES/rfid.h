#ifndef RFID_H
#define RFID_H

#include<LPC17xx.h>
#include<stdint.h>

void rfid_init(void);
char rfid_read(void);

#endif
