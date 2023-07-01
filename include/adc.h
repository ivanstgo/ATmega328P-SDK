#ifndef ADC_H
#define ADC_H
volatile unsigned int adc_value;
void adc_init(void);
unsigned int adc_start(unsigned char pin);
void adc_free_running_mode(unsigned char pin);
#endif