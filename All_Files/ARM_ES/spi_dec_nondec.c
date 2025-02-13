// To interface MAX7219 slave SPI to LPC1768 SSP1 
// P0.7 = sclk  P0.8 = MISO   P0.9 = MOSI  & P0.6 as GPIO to select slave
#include <LPC17xx.h>

#define CS (1 << 6)

void ssp_spi_init(void);
void ssp_spi_write(uint16_t data);
void delay_ms(uint32_t ms);

int main()
{
 ssp_spi_init();        //perform basic confiuration/setup for ssp-spi communication
 
 ssp_spi_write(0x0C01); // write 1 to shutdown register
 ssp_spi_write(0x0A0F);	// write F to intensity register i.e max. intensity

 
 while(1)
 {
  ssp_spi_write(0x0B02);// scan digit-0,1,2
  ssp_spi_write(0x0900);// operate digit-0,1,2 in non-decode mode
 
  ssp_spi_write(0x010E);// write 'L' to digit-0 display unit
  ssp_spi_write(0x0267);// write 'P' to digit-1 display unit
  ssp_spi_write(0x034E);// write 'C' to digit-2 display unit
 
  delay_ms(1000);
  
  ssp_spi_write(0x0B03);// scan digit-0,1,2,3
  ssp_spi_write(0x090F);// operate digit-0,1,2,3 in decode mode
 
  ssp_spi_write(0x0101);// write 1 to digit-0 display unit
  ssp_spi_write(0x0207);// write 7 to digit-1 display unit
  ssp_spi_write(0x0306);// write 6 to digit-2 display unit
  ssp_spi_write(0x0408);// write 8 to digit-0 display unit
  delay_ms(1000);
 }
 
}

void ssp_spi_init(void)
 {
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

 
void ssp_spi_write(uint16_t data)
{
  

  LPC_GPIO0->FIOCLR |= CS; // connect to slave
  while(!(LPC_SSP1->SR & (1 << 1))){}// wait if fifo is full
  
  LPC_SSP1->DR = data;// write to shutdown register 1 for normal operation
  while((LPC_SSP1->SR & (1 << 4))){}// wait if it is busy (not idle)
  
  LPC_GPIO0->FIOSET |= CS; // disconnect slave
 
 }

void delay_ms(uint32_t ms)
{
 uint32_t i , j ;
 for(i = 0 ; i < ms ; i ++ )
 {
  for(j = 0 ; j < 2000 ; j ++ )	{ }
 
 }

}