/**
 * @file adc.h
 * @author Iván Santiago
 * @date 07-01-2023 17:43
 * @brief Library to use ATmega328P ADC
*/
#ifndef _ADC_H_
#define _ADC_H_
/**
 * Stores the value of the last convertion
*/
volatile unsigned int adc_value;
/**
 * Inits ADC
*/
void adc_init(void);
/**
 * Start an ADC conversion
 * @param pin analog pin to perform the conversion
*/
unsigned int adc_start(unsigned char pin);
/**
 * Start conversion auto-triggered by the ADC interrupt
 * @param pin analog pin to perform the conversion
*/
void adc_free_running_mode(unsigned char pin);
#endif