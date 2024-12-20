#ifndef SPI_H
#define SPI_H

# include <LPC17xx.h>

#define CS (1 << 6)

void ssp_spi_init(void);
void ssp_spi_write(uint16_t data);
void delay(uint32_t ms);
#endif
