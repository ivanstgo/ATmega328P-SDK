#ifndef TIMERS_H
#define TIMERS_H
#define NORMAL_MODE 0
#define CTC_MODE 1
#define FAST_PWM_MODE 2
#define PHASE_CORRECT_PWM_MODE 3
#define PHASE_AND_FREQUENCY_CORRECT_PWM 4
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
 * Contains the elapsed time after call start_micros function
*/
volatile unsigned long microseconds;
volatile unsigned long milliseconds;
void TC0_init(char mode);
void TC1_init(char mode);
void TC2_init(char mode);
void TC0_set_frequency(float frequency);
void TC1_set_frequency(float frequency);
void TC2_set_frequency(float frequency);
void TC0_set_pulse_width(float width);
void TC1_set_pulse_width(float width);
void TC2_set_pulse_width(float width);
void start_micros(void);
void start_millis(void);
#endif