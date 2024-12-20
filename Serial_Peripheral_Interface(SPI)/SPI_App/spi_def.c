# include "spi.h"

void ssp_spi_init(void){
    LPC_GPIO0->FIODIR |= CS ; // configure P0.6 pin as GPIO Output pin

    LPC_SC->PCONP |= (1 << 10);// power-on ssp1 module
    
    LPC_PINCON->PINSEL0 |=   (1 << 19)|(1 << 17)|(1 << 15);  // configure P0.7-P0.9 as SSP1 pins
    LPC_PINCON->PINSEL0 &= ~((1 << 18)|(1 << 16)|(1 << 14));

    LPC_SC->CLKSRCSEL = 0x00; // select clock source as RC osc  i.e cclk = 4MHz
    LPC_SC->PCLKSEL0 &= ~(0x03 << 20);// pclk = cclk/4 = 1MHz

    LPC_SSP1->CR0 |= 0x0B; // data length = 12 bits per transfer
    LPC_SSP1->CR0 &= ~(0x03<<4); // configure SSP1 as SPI
    LPC_SSP1->CR0 &= ~(0x03<<6); // select mode-0 operation
    LPC_SSP1->CR0 &= ~(0xFF<<8); // select serial clock rate as 1 i.e (0+1)

    LPC_SSP1->CR1 &= ~(0x01<<0);// select normal operation
    LPC_SSP1->CR1 &= ~(0x01<<2);// select master mode
    LPC_SSP1->CPSR = 20; // SCLK Speed = PCLK/(CPSR*(SCR+1)) = 1MHz/(20 * (0+1)) = 50KHz

    LPC_SSP1->CR1 |= (1 << 1); // enable/start ssp/spi operation 
}

void ssp_spi_write(uint16_t data){
    LPC_GPIO0->FIOCLR |= CS; // connect to slave
    while(!(LPC_SSP1->SR & (1 << 1))) {}// wait if fifo is full
    
    LPC_SSP1->DR = data;// write to shutdown register 1 for normal operation
    while((LPC_SSP1->SR & (1 << 4))) {}// wait if it is busy (not idle)
    
    LPC_GPIO0->FIOSET |= CS; // disconnect slave
}

void delay(uint32_t ms){
    uint32_t i, j;
    for(i = 0; i < ms; i++){
        for(j = 0; j < 2000; j++)	{}
    }
}
