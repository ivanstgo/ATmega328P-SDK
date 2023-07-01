#ifndef I2C_H
#define I2C_H
/**
 * Macro to format I2C slave address to write SLA + W
*/
#define SLA_W(SLA) (SLA) << 1
/**
 * Macro to format I2C slave address to read SLA + R
*/
#define SLA_R(SLA) ((SLA) << 1) | 0x01
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);
#endif