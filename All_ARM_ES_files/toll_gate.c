#include<string.h>

#define ROWS (0XF<<4)
#define COLS (0XF<<0)

void uart_init(void);
char uart_byte_receive(void);
void uart_string_receive(char *buffer, int maxLength);
void uart_string_transmit(const char *buffer);
void uart_byte_transmit(char data);
void key_main_prog(void);
void delay(unsigned int ms);
void PWM_Init(void) {
    // Set P2.4 as PWM output (PWM1.5)
    LPC_PINCON->PINSEL3 |= (1 << 17);  // Configure P2.4 as PWM1.5
    LPC_PWM1->TCR = 0x02;             // Reset the PWM counter and prescaler
    LPC_PWM1->PR = 0;                 // No prescaler
    LPC_PWM1->MCR = (1 << 1);         // Reset on PWMMR0 match
    LPC_PWM1->MR0 = 20000;            // Set period to 20ms (50Hz for servo)
    LPC_PWM1->MR5 = 1500;             // Default pulse width (1.5ms -> 90 degrees)
    LPC_PWM1->LER = (1 << 0) | (1 << 5); // Enable updates to MR0 and MR5
    LPC_PWM1->PCR = (1 << 13);        // Enable PWM1.5 output
    LPC_PWM1->TCR = (1 << 0) | (1 << 3); // Enable counter and PWM mode
}

void Servo_SetAngle(uint32_t angle) 
{
    // Map angle (0 to 180) to pulse width (1000us to 2000us)
    uint32_t pulse_width = 1000 + ((angle * 1000) / 180); // 1ms to 2ms
    LPC_PWM1->MR5 = pulse_width;      // Set pulse width for PWM1.5
    LPC_PWM1->LER = (1 << 5);         // Latch the new MR5 value
}

void pwm_main() 
{
    PWM_Init();   // Initialize PWM for the servo motor
    Servo_SetAngle(150);  // Rotate servo to 90 degree
	delay(2500);
	Servo_SetAngle(0);
}
void key_main_prog()
{
    int money=10000;
    char cardID[20]; // Buffer for received RFID data
	char money1[30];
    const char validCardID[] = "17920966";  // The expected RFID card UID
	const char validCardID1[] = "5407BD23";
  while (1) 
	{
	  	//lcd_cmd_write(0X01);
		lcd_str_write("Scan RFID Card");
		delay(200);
        uart_string_receive(cardID, sizeof(cardID));  // Receive Card ID
        delay(100);
		lcd_cmd_write(0X01);
		LPC_GPIO1->FIOCLR=(0XFF<<19)|(1<<27); 
        
        // Compare received ID with the stored validCardID
        if (strcmp(cardID, validCardID) == 0) 
		{	
		      money=money-5;
			  sprintf(money1, "MONEY = %d", money);
			 lcd_str_write(money1);
			 lcd_cmd_write(0X01);
             lcd_str_write("Happy journey");  // Display message on LCD
			 lcd_cmd_write(0X01);
			 pwm_main();
			 LPC_GPIO1->FIOSET=(0XFF<<19)|(1<<27);
			 delay(1000);
			 LPC_GPIO1->FIOCLR=(0XFF<<19)|(1<<27);
        } 
		if (strcmp(cardID, validCardID1)== 0)  
		{ 
		     lcd_str_write("WAIT SOME TIME");  // Display message on LCD
			 lcd_cmd_write(0X01);
        }
		delay(500);
    }
 }
 void uart_init() 
 {                            
    LPC_PINCON->PINSEL0 |= (1 << 4);     // P0.2 as UART0 TX
    LPC_PINCON->PINSEL0 &= ~(1 << 5);
    LPC_PINCON->PINSEL0 |= (1 << 6);     // P0.3 as UART0 RX
    LPC_PINCON->PINSEL0 &= ~(1 << 7);
   
    LPC_SC->PCONP |= (1 << 3);  // Enable UART0

    LPC_SC->PCLKSEL0 &= ~((1 << 7) | (1 << 6));  // PCLK = CCLK/4 = 1MHz

    LPC_UART0->LCR = 0x03;      // 8-bit, no parity, 1 stop bit
    LPC_UART0->LCR |= (1 << 7); // Enable divisor latch

    LPC_UART0->DLM = 0x00;
    LPC_UART0->DLL = 0x06;      // Set baud rate 9600
    LPC_UART0->FDR = 0xC1;      // Fractional divider settings
    LPC_UART0->FCR = 0x07;      // Enable FIFO
    LPC_UART0->LCR &= ~(1 << 7); // Disable divisor latch
}

char uart_byte_receive(void) 
{
    while ((LPC_UART0->LSR & (1 << 0)) == 0); // Wait for data
    return LPC_UART0->RBR;
}

void uart_string_receive(char *buffer, int maxLength) 
{
    int i = 0;
    char ch;
    while (i < maxLength - 1) 
	{
        ch = uart_byte_receive();
        if (ch == '\n' || ch == '\r') break;  // Stop at newline
        buffer[i++] = ch;
    }
    buffer[i] = '\0';  // Null-terminate the string
}

// Function to send a single character via UART
void uart_byte_transmit(char data) 
{
    while ((LPC_UART0->LSR & (1 << 5)) == 0); // Wait for transmitter to be ready
    LPC_UART0->THR = data;
}

// Function to send a string via UART
void uart_string_transmit(const char *buffer)
{
    while (*buffer) 
	{
        uart_byte_transmit(*buffer++);
    }
}
