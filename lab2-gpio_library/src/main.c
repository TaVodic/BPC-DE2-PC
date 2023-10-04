/***********************************************************************
 * 
 * Blink two LEDs in Arduino-, register-, and library-style. Use 
 * function from delay library to slow down blinking.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5   // PB5 is AVR pin where green on-board LED is connected
#define LED_RED     PB0     // Off-board LED
#define Button      PD2
#define SHORT_DELAY 200 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <gpio.h>       // GPIO library for AVR-GCC


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
//#include "Arduino.h"
//#define PB5 13          // In Arduino world, PB5 is called "13"
//#define PB0 8
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle LEDs and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status

    // Set pins where LEDs are connected as output
    // Ver 1: Arduino style
    //pinMode(LED_GREEN, OUTPUT);
    //pinMode(LED_RED, OUTPUT);

    // Ver 2: Low-level (register) style
    //DDRB = DDRB | (1<<LED_GREEN);
    //DDRB = DDRB | (1<<LED_RED);

    // Ver 3: Library function style
    GPIO_mode_output(&DDRB, LED_GREEN);  // Set output mode in DDRB reg
    GPIO_mode_output(&DDRB, LED_RED);  // Set output mode in DDRB reg

    //GPIO_mode_input_pullup(&DDRD, Button);

    DDRD &= ~(1<<Button);
    PORTD |= (1<<Button); 

    // Infinite loop PIND &= (1<<PD0)
    while (1)
    {

        if((PIND &= (1<<Button)) == 0){
            // Change LED value
            if (led_value == 0) {
                led_value = 1;
                // Set pin(s) to HIGH
                // Ver 1:
                //digitalWrite(LED_GREEN, LOW);
                //digitalWrite(LED_RED, HIGH);
                // Ver 2:
                //PORTB |= (1<<LED_GREEN);
                //PORTB &= ~(1<<LED_RED);
                // Ver 3:
                GPIO_write_high(&PORTB, 5);
                GPIO_write_low(&PORTB, 0);

            }
            else {
                led_value = 0;
                // Clear pin(s) to LOW
                //digitalWrite(LED_GREEN, HIGH);
                //digitalWrite(LED_RED, LOW);
                //PORTB &= ~(1<<LED_GREEN);            
                //PORTB |= (1<<LED_RED);
                GPIO_write_high(&PORTB, 0);
                GPIO_write_low(&PORTB, 5);

            }
            // Pause several milliseconds
            _delay_ms(SHORT_DELAY);
        } else{
            PORTB &= ~(1<<LED_GREEN);
            PORTB &= ~(1<<LED_RED);
        }
    }

    // Will never reach this
    return 0;
}