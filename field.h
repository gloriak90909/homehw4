/**
 * @file field.h
 * @author Gloria Kim
 * 
 */

#ifndef FIELD_H
#define FIELD_H

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8


/**
 * This function performs the addition operation in the 8-bit Galois field used by AES. 
 * @param a First byte operand
 * @param b Second byte operand
 * @return returns the result of adding a and b
 */
byte fieldAdd( byte a, byte b );

/**
 * This function performs the subtraction operation in the 8-bit Galois field used by AES. 
 * @param a First byte operand
 * @param b Second byte operand
 * @return the result of subtracting b from a
 */
byte fieldSub( byte a, byte b );

/**
 * This function performs the multiplication operation in the 8-bit Galois field used by AES
 * @param a First byte operand
 * @param b Second byte operand 
 * @return the result of multiplying a and b
 */
byte fieldMul( byte a, byte b );

#endif
