/**
 * @file i2c.h
 * @author Iván Santiago
 * @date 07-01-2023 17:55
 * @brief Library to use ATmega328P I2C
*/
#ifndef _I2C_H_
#define _I2C_H_
/**
 * Macro to format I2C slave address to write SLA + W
*/
#define SLA_W(SLA) (SLA) << 1
/**
 * Macro to format I2C slave address to read SLA + R
*/
#define SLA_R(SLA) ((SLA) << 1) | 0x01
/**
 * Inits 2 Wire Serial Interface.
 * TWBR = (F_CPU - 16 * SCLF) / (SCLF * 2 * N)
 */
void i2c_init(void);
/**
 * Sends start condition
 */
void i2c_start(void);
/**
 * Sends stop condition
 */
void i2c_stop(void);
/**
 * Writes a byte using Two Wire Interface
 * @param data the byte to write
 */
void i2c_write(unsigned char data);
/**
 * Reads a byte using Two Wire Interface
 * @return the byte read
 */
unsigned char i2c_read(void);
#endif