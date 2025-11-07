/**
 * @file aes.c
 * @author Gloria Kim
 * This is where the AES algorithms for encryption and decryption are implemented. 
 * It’s broken up into several small functions for the various steps, so these can be tested and debugged independently.
 */

#include "aes.h"


// /**
//  * This function fills in the subkey array with subkeys for each round of AES, computed from the given key.
//  * @param subkey a 2d array that will be filled with the round subkeys
//  * @param key the original 16-byte AES key
//  */
// void generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] ) {

// }

// /**
// * This function performs the addSubkey operation, adding the given subkey (key) to the given data array.
//  * @param data 16-byte array representing the current AES state
//  * @param key 16-byte round subkey to be added to the state
//  */
// void addSubkey( byte data[ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] ) {

// }

// /**
//  * This function rearranges a block of 16 data values from the one-dimensional arrangement to the 4 × 4 arrangement.
//  * @param square 4x4 array that will be filled with the rearranged data values
//  * @param data 16-byte array representing the current AES state
//  */
// void blockToSquare( byte square[ BLOCK_ROWS ][ BLOCK_COLS ], byte const data[ BLOCK_SIZE ] )
// {
//     for (int r = 0; r < BLOCK_ROWS; r++) {
//         for (int c = 0; c < BLOCK_COLS; c++) {
//             square[r][c] = data[c * BLOCK_ROWS + r];
//         }
//     }
// }

// /**
//  * This function rearranges a 4 × 4 arrangement of data values, returning them 
//  * as a one-dimensional array of 16 values.
//  * @param data 16-byte array that will be filled with the rearranged data values
//  * @param square 4x4 array representing the current AES state 
//  */
// void squareToBlock( byte data[ BLOCK_SIZE ], byte const square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {

// }

// /**
//  * This function performs the shiftRows operation on the given 4 × 4 square of values.
//  * @param square 4x4 array representing the current AES state
//  */
// void shiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {

// }

// /**
//  * This function performs the inverse shiftRows operation on the given 4 × 4 square of values.
//   * @param square 4x4 array representing the current AES state
//  */
// void unShiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {

// }

// /**
//  * This function performs the mixColumns operation on the given 4 × 4 square of values, multiplying each column by the matrix shown in the requirements section.
//   * @param square 4x4 array representing the current AES state
//  */
// void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {

// }


// /**
//  * This function performs the inverse of the mixColumns operation on the given 4 × 4 square of values, 
//  * multiplying each column by the inverse of the mixColumns matrix shown in the requirements section.
//  * @param square 4x4 array representing the current AES state
//  */
// void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {

// }


// /**
//  * This function encrypts a 16-byte block of data using the given key. 
//  * It generates the 11 subkeys from key, adds the first subkey, then performs the 10 rounds of operations needed to encrypt the block.
//  * @param data 16-byte array representing the current AES state
//  * @param key 16-byte AES key used to encrypt the data
//  */
// void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {

// }

// /**
//  * This function decrypts a 16-byte block of data using the given key. 
//  * It generates the 11 subkeys from key, then performs the 10 rounds of inverse operations (and then an addSubkey) to decrypt the block.
//  * @param data 16-byte array representing the current AES state
//  * @param key 16-byte AES key used to decrypt the data
//  */
// void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {

// }
