#include <LPC17xx.h>

#define RS_PIN (1 << 10) // RS connected to P0.10
#define EN_PIN (1 << 11) // EN connected to P0.11
#define VALUE_PINS (0xFF << 15) // Data pins connected to P0.15 - P0.22

// Function declarations
void lcd_cmd_write(char cmd);
void lcd_dat_write(char data);
void delay_ms(uint32_t millis);
void lcd_str_write(char *pstr);
void lcd_init(void);

/* lcd.c */
#include "lcd.h"
#include <stdio.h>

void lcd_cmd_write(char cmd) {
    LPC_GPIO0->FIOCLR = VALUE_PINS;
    LPC_GPIO0->FIOSET = (cmd << 15);
    LPC_GPIO0->FIOCLR = RS_PIN;
    LPC_GPIO0->FIOSET = EN_PIN;
    delay_ms(5);
    LPC_GPIO0->FIOCLR = EN_PIN;
}

void lcd_dat_write(char data) {
    LPC_GPIO0->FIOCLR = VALUE_PINS;
    LPC_GPIO0->FIOSET = (data << 15);
    LPC_GPIO0->FIOSET = RS_PIN;
    LPC_GPIO0->FIOSET = EN_PIN;
    delay_ms(5);
    LPC_GPIO0->FIOCLR = EN_PIN;
}

void lcd_str_write(char *pstr) {
    while (*pstr) {
        lcd_dat_write(*pstr);
        pstr++;
    }
}

void delay_ms(uint32_t millis) {
	uint32_t i;
    for (i = 0; i < millis * 1250; i++);
}

void lcd_init(void) {
    LPC_GPIO0->FIODIR |= RS_PIN | EN_PIN | VALUE_PINS;
    delay_ms(100);
    lcd_cmd_write(0x38); // 8-bit, 2-line
    lcd_cmd_write(0x0C); // Display on, cursor off
    lcd_cmd_write(0x01); // Clear display
}

/* main.c */
#include <LPC17xx.h>
#include "lcd.h"
#include <stdio.h>
#include <string.h>

#define UART3_TX_PIN (1 << 0)
#define UART3_RX_PIN (1 << 1)

void UART3_Init(void) {
    LPC_SC->PCONP |= (1 << 25);
    LPC_PINCON->PINSEL9 |= (3 << 24) | (3 << 26);
    LPC_UART3->LCR = (3 << 0) | (1 << 7);
    LPC_UART3->DLM = 0;
    LPC_UART3->DLL = 13;
    LPC_UART3->LCR &= ~(1 << 7);
    LPC_UART3->FCR = (1 << 0) | (1 << 1) | (1 << 2);
}

char UART3_ReceiveChar(void) {
    while (!(LPC_UART3->LSR & (1 << 0)));
    return LPC_UART3->RBR;
}

void UART3_ReceiveString(char *buffer, int maxLength) {
    int i = 0;
    char ch;
    while (i < maxLength - 1) {
        ch = UART3_ReceiveChar();
        if (ch == '\n' || ch == '\r') break;
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}

int main(void) {
    char cardUID[20];
    lcd_init();
    UART3_Init();
    lcd_cmd_write(0x01);
    lcd_str_write("Scan RFID Card");
    delay_ms(500);

    while (1) {
        UART3_ReceiveString(cardUID, sizeof(cardUID));
        lcd_cmd_write(0x01);
        lcd_str_write("Card UID:");
        lcd_cmd_write(0xC0);
        lcd_str_write(cardUID);
        delay_ms(2000);
        
        if (strcmp(cardUID, "5407BD23") == 0) {
            lcd_cmd_write(0x01);
            lcd_str_write("Access Granted");
        } else {
            lcd_cmd_write(0x01);
            lcd_str_write("Access Denied");
        }
        delay_ms(2000);
        lcd_cmd_write(0x01);
        lcd_str_write("Scan RFID Card");
    }
}
