#include "timers.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

Configuration config;

/**
 * Configures Timer/Counter 0
 * @param mode mode of operation
 */
void TC0_init(char mode)
{
    TCCR0A = 0;
    TCCR0B = 0;
    switch (mode)
    {
    case CTC_MODE:
        TCCR0A |= (1 << COM0A0) | (1 << WGM01);
        config.mode_TC0 = CTC_MODE;
        break;
    case FAST_PWM_MODE:
        TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
        TCCR0B |= 1 << WGM02;
        config.mode_TC0 = FAST_PWM_MODE;
        break;
    case PHASE_CORRECT_PWM_MODE:
        TCCR0A |= (1 << COM0B1) | (1 << WGM00);
        TCCR0B |= 1 << WGM02;
        config.mode_TC0 = PHASE_CORRECT_PWM_MODE;
        break;
    default:
        config.mode_TC0 = NORMAL_MODE;
        break;
    }
}

/**
 * Sets Timer/Counter 0 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 30.5176 Hz.
 * In Fast PWM Mode minimum frequency is 61.0352 Hz.
 */
void TC0_set_frequency(float frequency)
{
    float n = F_CPU / (256 * frequency);
    if (n <= 1)
    {
        TCCR0B |= 1;
        config.prescaler_TC0 = 1;
        n = 1.0;
    }
    else if (n > 1 && n <= 8)
    {
        TCCR0B |= 2;
        config.prescaler_TC0 = 2;
        n = 8.0;
    }
    else if (n > 8 && n <= 64)
    {
        TCCR0B |= 3;
        config.prescaler_TC0 = 3;
        n = 64.0;
    }
    else if (n > 64 && n <= 256)
    {
        TCCR0B |= 4;
        config.prescaler_TC0 = 4;
        n = 256.0;
    }
    else
    {
        TCCR0B |= 5;
        config.prescaler_TC0 = 5;
        n = 1024.0;
    }
    switch (config.mode_TC0)
    {
    case CTC_MODE:
        OCR0A = (unsigned char)(F_CPU / (2 * n * frequency) - 1);
        break;
    case FAST_PWM_MODE:
        OCR0A = (unsigned char)(F_CPU / (n * frequency) - 1);
        break;
    case PHASE_CORRECT_PWM_MODE:
        OCR0A = (unsigned char)(F_CPU / (2 * n * frequency));
        break;
    default:
        break;
    }
    TCNT0 = 0;
}

/**
 * Sets Timer/Counter 0 pulse width
 * @param width pulse width in seconds
 */
void TC0_set_pulse_width(float width)
{
    float n;
    switch (config.prescaler_TC0)
    {
    case 1:
        n = 1.0;
        break;
    case 2:
        n = 8.0;
        break;
    case 3:
        n = 64.0;
        break;
    case 4:
        n = 256.0;
        break;
    case 5:
        n = 1024.0;
        break;
    default:
        n = 1.0;
        break;
    }
    switch (config.mode_TC0)
    {
    case FAST_PWM_MODE:
        OCR0B = (unsigned char)(F_CPU * width / n + 1);
        break;
    case PHASE_CORRECT_PWM_MODE:
        OCR0B = (unsigned char)(F_CPU * width / (2 * n) + 1);
        break;
    default:
        break;
    }
    TCNT0 = 0;
}

/**
 * Configures Timer/Counter 1
 * @param mode mode of operation
 */
void TC1_init(char mode)
{
    TCCR1A = 0;
    TCCR1B = 0;
    switch (mode)
    {
    case CTC_MODE:
        TCCR1A |= (1 << COM1A0);
        TCCR1B |= (1 << WGM02);
        config.mode_TC1 = CTC_MODE;
        break;
    case FAST_PWM_MODE:
        TCCR1A |= (1 << COM1A1) | (1 << WGM11);
        TCCR1B |= (1 << WGM13) | (1 << WGM12);
        config.mode_TC1 = FAST_PWM_MODE;
        break;
    case PHASE_CORRECT_PWM_MODE:
        TCCR1A |= (1 << COM1A1) | (1 << WGM11);
        TCCR1B |= 1 << WGM13;
        config.mode_TC1 = PHASE_CORRECT_PWM_MODE;
        break;
    case PHASE_AND_FREQUENCY_CORRECT_PWM:
        TCCR1A |= 1 << COM1A1;
        TCCR1B |= 1 << WGM13;
        config.mode_TC1 = PHASE_AND_FREQUENCY_CORRECT_PWM;
        break;
    default:
        config.mode_TC1 = NORMAL_MODE;
        break;
    }
}

/**
 * Sets Timer/Counter 1 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 0.1192 Hz.
 * In Fast PWM Mode minimum frequency is 0.2384 Hz.
 */
void TC1_set_frequency(float frequency)
{
    float n = F_CPU / (65536.0 * frequency);
    if (n <= 1)
    {
        TCCR1B |= 1;
        config.prescaler_TC1 = 1;
        n = 1.0;
    }
    else if (n > 1 && n <= 8)
    {
        TCCR1B |= 2;
        config.prescaler_TC1 = 2;
        n = 8.0;
    }
    else if (n > 8 && n <= 64)
    {
        TCCR1B |= 3;
        config.prescaler_TC1 = 3;
        n = 64.0;
    }
    else if (n > 64 && n <= 256)
    {
        TCCR1B |= 4;
        config.prescaler_TC1 = 4;
        n = 256.0;
    }
    else
    {
        TCCR1B |= 5;
        config.prescaler_TC1 = 5;
        n = 1024.0;
    }
    switch (config.mode_TC1)
    {
    case CTC_MODE:
        OCR1A = (unsigned int)(F_CPU / (2 * n * frequency) - 1);
        break;
    case FAST_PWM_MODE:
        ICR1 = (unsigned int)(F_CPU / (n * frequency) - 1);
        break;
    case PHASE_CORRECT_PWM_MODE:
        ICR1 = (unsigned int)(F_CPU / (2 * n * frequency));
        break;
    case PHASE_AND_FREQUENCY_CORRECT_PWM:
        ICR1 = (unsigned int)(F_CPU / (2 * n * frequency));
        break;
    default:
        break;
    }
    TCNT1 = 1;
}

/**
 * Sets Timer/Counter 1 pulse width
 * @param width pulse width in seconds
 */
void TC1_set_pulse_width(float width)
{
    TCCR1B &= 0xF8;
    float n;
    switch (config.prescaler_TC1)
    {
    case 1:
        n = 1.0;
        TCCR1B |= 1;
        break;
    case 2:
        n = 8.0;
        TCCR1B |= 2;
        break;
    case 3:
        n = 64.0;
        TCCR1B |= 3;
        break;
    case 4:
        n = 256.0;
        TCCR1B |= 4;
        break;
    case 5:
        n = 1024.0;
        TCCR1B |= 5;
        break;
    default:
        n = 1.0;
        break;
    }
    switch (config.mode_TC1)
    {
    case FAST_PWM_MODE:
        OCR1A = (unsigned int)(F_CPU * width / n);
        break;
    case PHASE_CORRECT_PWM_MODE:
        OCR1A = (unsigned int)(F_CPU * width / (2 * n));
        break;
    case PHASE_AND_FREQUENCY_CORRECT_PWM:
        OCR1A = (unsigned int)(F_CPU * width / (2 * n));
        break;
    default:
        break;
    }
    TCNT1 = 0;
}

/**
 * Configures Timer/Counter 2
 * @param mode mode of operation
 */
void TC2_init(char mode)
{
    TCCR2A = 0;
    TCCR2B = 0;
    switch (mode)
    {
    case CTC_MODE:
        TCCR2A |= (1 << COM2A0) | (1 << WGM21);
        config.mode_TC2 = CTC_MODE;
        break;
    case FAST_PWM_MODE:
        TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
        TCCR2B |= 1 << WGM22;
        config.mode_TC2 = FAST_PWM_MODE;
        break;
    case PHASE_CORRECT_PWM_MODE:
        TCCR2A |= (1 << COM2B1) | (1 << WGM20);
        TCCR2B |= 1 << WGM22;
        config.mode_TC2 = PHASE_CORRECT_PWM_MODE;
        break;
    default:
        config.mode_TC2 = NORMAL_MODE;
        break;
    }
}

/**
 * Sets Timer/Counter 2 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 30.5176 Hz.
 * In Fast PWM Mode minimum frequency is 61.0352 Hz.
 */
void TC2_set_frequency(float frequency)
{
    float n = F_CPU / (256 * frequency);
    if (n <= 1)
    {
        TCCR2B |= 1;
        config.prescaler_TC2 = 1;
        n = 1.0;
    }
    else if (n > 1 && n <= 8)
    {
        TCCR2B |= 2;
        config.prescaler_TC2 = 2;
        n = 8.0;
    }
    else if (n > 8 && n <= 32)
    {
        TCCR2B |= 3;
        config.prescaler_TC2 = 3;
        n = 32.0;
    }
    else if (n > 32 && n <= 64)
    {
        TCCR2B |= 4;
        config.prescaler_TC2 = 4;
        n = 64.0;
    }
    else if (n > 64 && n <= 128)
    {
        TCCR2B |= 5;
        config.prescaler_TC2 = 5;
        n = 128.0;
    }
    else if (n > 128 && n <= 256)
    {
        TCCR2B |= 6;
        config.prescaler_TC2 = 6;
        n = 256.0;
    }
    else
    {
        TCCR2B |= 7;
        config.prescaler_TC2 = 7;
        n = 1024.0;
    }
    switch (config.mode_TC2)
    {
    case CTC_MODE:
        OCR2A = (unsigned char)(F_CPU / (2 * n * frequency) - 1);
        break;
    case FAST_PWM_MODE:
        OCR2A = (unsigned char)(F_CPU / (n * frequency) - 1);
        break;
    case PHASE_CORRECT_PWM_MODE:
        OCR2A = (unsigned char)(F_CPU / (2 * n * frequency));
        break;
    default:
        break;
    }
    TCNT2 = 0;
}

/**
 * Sets Timer/Counter 2 pulse width
 * @param width pulse width in seconds
 */
void TC2_set_pulse_width(float width)
{
    float n;
    switch (config.prescaler_TC2)
    {
    case 1:
        n = 1.0;
        break;
    case 2:
        n = 8.0;
        break;
    case 3:
        n = 32.0;
        break;
    case 4:
        n = 64.0;
        break;
    case 5:
        n = 128.0;
        break;
    case 6:
        n = 256.0;
        break;
    case 7:
        n = 1024.0;
        break;
    default:
        n = 1.0;
        break;
    }
    switch (config.mode_TC2)
    {
    case FAST_PWM_MODE:
        OCR2B = (unsigned char)(F_CPU * width / n + 1);
        break;
    case PHASE_CORRECT_PWM_MODE:
        OCR2B = (unsigned char)(F_CPU * width / (2 * n) + 1);
        break;
    default:
        break;
    }
    TCNT2 = 0;
}

ISR(TIMER0_COMPA_vect)
{
    microseconds++;
}

/**
 * Start Timer/Counter 0 in normal mode.
 * Increases the value of the variable 'microseconds' every microsecond
 */
void start_micros(void)
{
    microseconds = 0;
    TCCR0B |= 1 << CS00;
    TIMSK0 = 0;
    TIMSK0 |= 1 << OCIE0A;
    OCR0A = 16;
    TCNT0 = 0;
    sei();
}

ISR(TIMER0_COMPB_vect)
{
    milliseconds++;
}

/**
 * Start Timer/Counter 0 in normal mode.
 * Increases the value of the variable 'milliseconds' every millisecond
 */
void start_millis(void)
{
    milliseconds = 0;
    TCCR0B |= (1 << CS01) | (1 << CS00);
    TIMSK0 = 0;
    TIMSK0 |= 1 << OCIE0B;
    OCR0B = 250;
    TCNT0 = 0;
    sei();
}