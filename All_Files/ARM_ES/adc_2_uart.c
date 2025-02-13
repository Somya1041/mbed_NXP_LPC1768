# include <LPC17xx.h>
# include "uart0.h"

#define CH_SEL (1 << 2)
#define CLK_DIV (0xFF << 8)
#define BURST_MODE (0x01 << 16)
#define POWER_UP (0x01 << 21)
#define START_CONV (0x01 << 24)
#define DONE_CONV (0x01U << 31)
#define TEMP_COEF 100.0f

int main(){
	uint32_t adc_val;
	float volt, temp;
	char sval[20];
	
	LPC_SC -> PCONP |= (1 << 12); //ENABLE ADC POWER

	LPC_PINCON -> PINSEL1 |= (1 << 18); //P0.25 IS CONFIGURED AS ADC CHANNEL 2 INPUT
	LPC_PINCON -> PINSEL1 &= ~(1 << 19);
	
	LPC_ADC -> ADCR |= CH_SEL; //SELECT ADC CHANNEL 2
	LPC_ADC -> ADCR &= ~CLK_DIV; //ADC CLK = PCLK / (0+1) = 1MHz
	LPC_ADC -> ADCR &= ~BURST_MODE; //SELECT ADC SOFTWARE MODE
	LPC_ADC -> ADCR |= POWER_UP; //MAKE ADC OPERATIONAL
	
	uart0_init();
	
	while(1){
		LPC_ADC -> ADCR |= START_CONV; //STARTS CONVERSION
		while((LPC_ADC -> ADGDR & DONE_CONV) == 0){} //WAIT FOR CONVERSION TO END
		
		adc_val = (LPC_ADC -> ADGDR >> 4) & 0xFFF;
		volt = adc_val *3.3/4096;
		temp = volt * TEMP_COEF;
		
		sprintf(sval, "Temp: %.2f C", temp);
		uart0_str_transmit(sval);
		
		delay(1000);
		new_line();
	}
}
