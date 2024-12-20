# NXP LPC1768 Development Code Repository

This repository contains a collection of code examples and projects for the **NXP LPC1768**, a 32-bit microcontroller based on the ARM Cortex-M3 architecture. The LPC1768 is widely known for its robust performance, power efficiency, and an array of peripherals suitable for embedded systems applications. It is an excellent choice for developers working on industrial automation, IoT, and general embedded system design.

The repository is organized into multiple sections, each demonstrating the functionality and implementation of specific peripherals and features of the LPC1768 microcontroller. These examples serve as a guide to help developers quickly prototype, understand, and utilize the LPC1768's capabilities.

---

# Walkthrough of Repository Sections

### 1. **ADC (Analog-to-Digital Converter)**
   - Demonstrates the use of the LPC1768's built-in ADC module to convert analog signals into digital values.
   - This section contains two file:
      - `adc_temp_read.c`: This code reads temperature data from an ADC channel on the LPC1768 microcontroller, converts the ADC value to voltage, and calculates the temperature. It then displays the temperature on an LCD in Celsius using the LCD module's API.
      - `adc_2_uart.c`: This code reads temperature data from an ADC channel on the LPC1768 microcontroller, converts the ADC value to voltage, calculates the temperature, and transmits the temperature data as a string via **UART0**. It uses UART for communication, making it suitable for serial data logging or monitoring.
   
   - Applications: Sensor interfacing, signal monitoring, and analog data processing.

### 2. **Buzzer**
   - Explains how to control a buzzer using GPIO pins on the LPC1768.
   - This section contains two file:
      - `buzzer.c`: This code toggles a buzzer connected to pin P1.27 of the LPC1768 microcontroller by setting and clearing the GPIO pin in a loop with a 250 ms delay. This creates a periodic on-off sound from the buzzer.
      - `rand_buzzer.c`: This code controls a buzzer connected to pin P1.27 of the LPC1768 microcontroller, toggling it on and off with random delays between 100 ms and 1000 ms. It generates 10 iterations of random on-off patterns using the `rand()` function for the delay intervals.

   - Applications: Audio notifications, alarms, and feedback systems.

### 3. **Count_Display**
   - Implements a simple counter displayed on a 7-segment display or similar output device.
   - Applications: Event counting, time tracking, and user feedback.

### 4. **LCD_Display**
   - Shows how to interface and display data on an LCD using the LPC1768.
   - Applications: User interfaces, data visualization, and debugging.

### 5. **Matrix_Keypad**
   - Provides code for interfacing a matrix keypad and reading user input.
   - This section contains two file:
      - `keypress.c`: This code interfaces a 4x4 matrix keypad with the LPC1768 microcontroller to detect key presses. It scans the keypad rows and columns, identifies the pressed key, and displays the corresponding character on the LCD.
      - `password_check.c`: This code implements a password authentication system using a 4x4 matrix keypad with the LPC1768 microcontroller. It prompts the user to enter a password, compares the entered password with a predefined correct password, and displays a message on the LCD indicating whether the password is correct or wrong.

   - Applications: Keypads for user interaction, input systems, and security applications.

### 6. **Pulse Width Modulation (PWM)**
   - Demonstrates generating PWM signals using the LPC1768.
   - Applications: Motor control, LED brightness control, and power management.

### 7. **Serial Peripheral Interface (SPI)**
   - Explains how to configure and use the SPI protocol on the LPC1768 for communication with SPI-compatible devices.
   - Applications: Communication with sensors, memory devices, and displays requiring high-speed data transfer.

### 8. **Switches**
   - Covers reading and debouncing switch inputs with the LPC1768.
   - Applications: User inputs, control panels, and interactive systems.

### 9. **Timer**
   - Showcases the use of timers for generating delays, measuring time intervals, and periodic task execution.
   - Applications: Time-sensitive operations, event scheduling, and real-time applications.

### 10. **UART (Universal Asynchronous Receiver-Transmitter)**
   - Demonstrates serial communication using UART.
   - Applications: Communication with sensors, modules, or other microcontrollers.

### 11. **Watchdog Timer**
   - Explains how to configure and use the Watchdog Timer to reset the system in case of a software fault.
   - Applications: System reliability and fault recovery.

---

## Datasheet and Schematic Diagram

This repository also includes:
- **LPC1768 Datasheet:** A comprehensive document containing technical specifications, pin configurations, and functional details of the LPC1768 microcontroller.
- **Schematic Diagram:** A detailed circuit schematic to help users understand hardware connections and get references while exploring the code examples.

These resources are located in the `Datasheet` folder and are invaluable for both beginners and advanced users in understanding the microcontroller's architecture and peripheral interfacing.

---

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/Somya1041/NXP_LPC1768.git
   ```
2. Navigate to the desired section to explore code examples and project files.

---

## Prerequisites

- **Hardware:**
  - NXP LPC1768 development board
  - Required peripherals (e.g., LCD, keypad, buzzer)
- **Software:**
  - ARM Keil uVision or equivalent IDE
  - Flashing tool compatible with LPC1768
