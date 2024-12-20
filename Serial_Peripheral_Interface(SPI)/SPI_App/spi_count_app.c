# include "spi.h"

int main(){
    uint8_t cnt = 0;

    ssp_spi_init();
    
    ssp_spi_write(0x0C01);// operating mode 
    ssp_spi_write(0x0A0F);// max intensity
    ssp_spi_write(0x0B01);// scan only digit-0,1
    ssp_spi_write(0x0903);// operate digit-0,1 in decode mode

    while(1){
      ssp_spi_write((0x01<<8)|(cnt/10));
      ssp_spi_write((0x02<<8)|(cnt%10));
      cnt++;

      if (cnt == 100) { 
          cnt = 0 ;
      }

      delay_ms(200);
    }
}
