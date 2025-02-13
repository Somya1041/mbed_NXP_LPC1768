# include <LPC17xx.h>
# include <stdint.h>
#define BUZZER (1 << 27)
#define SWITCH (1 << 11)

void delay(uint32_t ms){
uint32_t i, j;
	for(i = 0; i < ms; i++){
		for(j = 0; j < 1250; j++){}
}
}

int main(){
	LPC_GPIO1 -> FIODIR |= BUZZER; //OUTPUT KE LIYE OR 
	LPC_GPIO2 -> FIODIR &= ~SWITCH;//INPUT KE LIYE AND
	LPC_GPIO1 -> FIOCLR = BUZZER;
	
	while(1){
		if ((LPC_GPIO2 -> FIOPIN & SWITCH) != 0){
			LPC_GPIO1 -> FIOSET = BUZZER;
		}
		
		else{
			LPC_GPIO1 -> FIOCLR = BUZZER;
		}
	}
	
}
