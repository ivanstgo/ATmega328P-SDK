#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Inits ADC
*/
void adc_init(void)
{
    ADMUX |= 1 << REFS0;
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

}

/**
 * Start an ADC conversion
 * @param pin analog pin to perform the conversion
*/
unsigned int adc_start(unsigned char pin)
{
    ADMUX &= 0b11111000;
    ADMUX |= 0x0F & pin;
    ADCSRA |= 1 << ADSC;
    while (!(ADCSRA & (1 << ADIF)))
        ;
    ADCSRA|=1<<ADIF;
    return ADC;
}

ISR(ADC_vect){
    adc_value = ADC;
}

/**
 * Start conversion auto-triggered by the ADC interrupt
 * @param pin analog pin to perform the conversion
*/
void adc_free_running_mode(unsigned char pin)
{
    ADMUX &= 0b11111000;
    ADMUX |= 0x0F & pin;
    ADCSRA |= (1 << ADATE) | (1 << ADIE);
    sei();
    ADCSRA |= 1 << ADSC;
}