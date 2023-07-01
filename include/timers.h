/**
 * @file timers.h
 * @author Iván Santiago
 * @date 07-01-2023 17:12
 * @brief Library to use ATmega328P timers
*/
#ifndef _TIMERS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#warning F_CPU no defined using F_CPU 16000000UL
#endif

#define NORMAL_MODE 0
#define CTC_MODE 1
#define FAST_PWM_MODE 2
#define PHASE_CORRECT_PWM 3
#define FREQUENCY_CORRECT_PWM 4

typedef struct configuration
{
    unsigned int prescaler_TC0 : 3;
    unsigned int mode_TC0 : 2;
    unsigned int prescaler_TC1 : 3;
    unsigned int mode_TC1 : 3;
    unsigned int prescaler_TC2 : 3;
    unsigned int mode_TC2 : 2;
} Configuration;
/**
 * Contains the elapsed time after the call to the count_micros function
*/
volatile unsigned long microseconds;
/**
 * Contains the elapsed time after the call to the count_millis function
*/
volatile unsigned long milliseconds;

/**
 * Configures Timer/Counter 0
 * @param mode mode of operation
 */
void TC0_init(char mode);
/**
 * Configures Timer/Counter 1
 * @param mode mode of operation
 */
void TC1_init(char mode);
/**
 * Configures Timer/Counter 2
 * @param mode mode of operation
 */
void TC2_init(char mode);
/**
 * Sets Timer/Counter 0 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 30.5176 Hz.
 * In Fast PWM Mode minimum frequency is 61.0352 Hz.
 */
void TC0_set_frequency(float frequency);
/**
 * Sets Timer/Counter 1 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 0.1192 Hz.
 * In Fast PWM Mode minimum frequency is 0.2384 Hz.
 */
void TC1_set_frequency(float frequency);
/**
 * Sets Timer/Counter 2 signal frequency
 * @param frequency signal frequency in Hz.
 * In CTC mode and Phase Correct Mode minimum frequency is 30.5176 Hz.
 * In Fast PWM Mode minimum frequency is 61.0352 Hz.
 */
void TC2_set_frequency(float frequency);
/**
 * Sets Timer/Counter 0 pulse width
 * @param width pulse width in seconds
 */
void TC0_set_pulse_width(float width);
/**
 * Sets Timer/Counter 1 pulse width
 * @param width pulse width in seconds
 */
void TC1_set_pulse_width(float width);
/**
 * Sets Timer/Counter 2 pulse width
 * @param width pulse width in seconds
 */
void TC2_set_pulse_width(float width);
/**
 * Start Timer/Counter 0 in normal mode.
 * Increases the value of the variable 'microseconds' every microsecond
 */
void count_micros(void);
/**
 * Start Timer/Counter 0 in normal mode.
 * Increases the value of the variable 'milliseconds' every millisecond
 */
void count_millis(void);
#endif