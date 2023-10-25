/***********************************************************************
 * 
 * Use USART unit and transmit data between ATmega328P and computer.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and transmit UART data four times 
 *           per second.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize USART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));
    
    // Configure 16-bit Timer/Counter1 to transmit UART data
    // Set prescaler to 262 ms and enable overflow interrupt
    TIM1_OVF_ENABLE
    TIM1_OVF_262MS

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("Print one line... ");
    uart_puts("done\r\n");

    uart_puts("\x1b[4;32m");  // 4: underline style; 32: green foreground
    uart_puts("This is all Green and Underlined\r\n");
    uart_puts("\x1b[0m");     // 0: reset all attributes
    uart_puts("This is Normal text again\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Transmit UART data four times per second.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    /*static uint8_t presc = 0;

    if (presc > 3){
        uart_puts("Paris\n\r");
        presc = 0;
    }
    presc++;*/

    uint8_t value;
    char string[8];  // String for converted numbers by itoa()

    value = uart_getc();
    if (value != '\0') {  // Data available from UART
        itoa(value, string, 10);
        uart_puts("Dec: ");
        uart_puts(string);
        uart_puts("     ");
        itoa(value, string, 16);
        uart_puts("Hex: ");
        uart_puts(string);
        uart_puts("     ");
        itoa(value, string, 2);
        uart_puts("Bin: ");
        uart_puts(string);
        uart_puts("\n\r");        
    }
}