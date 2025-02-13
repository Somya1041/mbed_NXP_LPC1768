# include <LPC17xx.h>
# include <stdlib.h>
# include <time.h>
#define BUZZER (0x01 << 27)

void delay_ms(uint32_t mls){
uint32_t i, j;
for (i = 0; i < mls; i++){
for (j = 0; j < 1250; j++){}
}
}

int main(){
uint32_t i;
LPC_GPIO1 -> FIODIR |= BUZZER;
LPC_GPIO1 -> FIOCLR = BUZZER;

for (i = 0; i < 10; i++){
        int rand_val = (rand() % (1000 - 100 + 1));
		
		LPC_GPIO1 -> FIOSET = BUZZER;
		delay_ms(rand_val);
		
		LPC_GPIO1 -> FIOCLR = BUZZER;
		delay_ms(rand_val);
		
    }
}
