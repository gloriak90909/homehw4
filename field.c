/**
 * @file field.c
 * @author Gloria Kim
 * This component implements support for basic arithmetic operations in an 8-bit (a byte) Galois field. 
 * These operations are used internally by AES for many steps in the encryption and decryption process.
 * Components include addition, subtraction, and multiplication used by AES. 
 */

#include "field.h"

/**
 * This function performs the addition operation in the 8-bit Galois field used by AES. 
 * @param a First byte operand
 * @param b Second byte operand
 * @return returns the result of adding a and b
 */
byte fieldAdd( byte a, byte b ) {
    return a^b;
}


/**
 * This function performs the subtraction operation in the 8-bit Galois field used by AES. 
 * @param a First byte operand
 * @param b Second byte operand
 * @return the result of subtracting b from a
 */
byte fieldSub( byte a, byte b ) {
  // byte result = a|b;
    return a^b;
} 

/**
 * This function performs the multiplication operation in the 8-bit Galois field used by AES
 * @param a First byte operand
 * @param b Second byte operand 
 * @return the result of multiplying a and b
 */
byte fieldMul( byte a, byte b ) {


  //byte a = 00111011
  //byte b = 01010111

  unsigned short short_a = (unsigned short)(a);
  unsigned short short_b = (unsigned short)(b);

  unsigned short result = 0x0000;


  for (int i = 0; i < 8; i++) {

    // shift a left by i
    if ( (short_b & (1 << i)) != 0 ) {
      result ^= (short_a << i);      
    }

  }

  int count = 0;
  //reading from left to right 
  for (int i = 15; i >= 8; i--) {
    if ( ((result & (1 << i)) != 0 ) && (result > 0x7F) ) {
      count++;
      unsigned short mod = 0x1B;
      result ^= (mod << (i - 8));
    }
  }
    
  return result & 0x00FF;
}
