/**
 * @file iostring.h
 * @author Iván Santiago
 * @date 07-01-2023 18:00
 * @brief Library to convert numeric types to string
*/
#ifndef _IOSTRING_H_
#define _IOSTRING_H_
/**
 * Converts a 16 bit signed integer to string of characters
 * @param a integer to convert
 * @return a string that contains the decimal representation of the integer
 */
const char *int2string(int a);
/**
 * Converts a 16 bit unsigned integer to string of characters
 * @param a integer to convert
 * @return a string that contains the decimal representation of the integer
 */
const char *uint2string(unsigned int a);
/**
 * Converts a unsigned char to string of characters
 * @param a byte to convert
 * @return a string that contains the hexadecimal representation of the byte
 */
const char *byte2hstring(unsigned char a);
/**
 * Converts a float to string character
 * @param a float to convert
 * @param n number of digits after point
 * @return a string that contains the decimal representation the float
 */
const char *float2string(float a, unsigned char n);
#endif