/**
 * @file aes.c
 * @author Gloria Kim
 * This is where the AES algorithms for encryption and decryption are implemented. 
 * It’s broken up into several small functions for the various steps, so these can be tested and debugged independently.
 */

#include "aes.h"
#include "aesUtil.h"


/**
 * This function fills in the subkey array with subkeys for each round of AES, computed from the given key.
 * @param subkey a 2d array that will be filled with the round subkeys
 * @param key the original 16-byte AES key
 */
void generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] ) {
  
}

/**
* This function performs the addSubkey operation, adding the given subkey (key) to the given data array.
 * @param data 16-byte array representing the current AES state
 * @param key 16-byte round subkey to be added to the state
 */
void addSubkey( byte data[ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] ) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
      data[i] = data[i] ^ key[i];
  }
}

/**
 * This function rearranges a block of 16 data values from the one-dimensional arrangement to the 4 × 4 arrangement.
 * @param square 4x4 array that will be filled with the rearranged data values
 * @param data 16-byte array representing the current AES state
 */
void blockToSquare( byte square[ BLOCK_ROWS ][ BLOCK_COLS ], byte const data[ BLOCK_SIZE ] )
{
  //a b c d   e f g h  i j k l  m n o p 

  //a e i m
  //b f j n
  //c g k o
  //d h l p

  //index = 6   g  [2][1] = data[ 1 * 4 + 2 ]  
  //square[r][c] = data[ c * BLOCK_ROWS + i ]

    for (int i = 0; i < BLOCK_ROWS; i++) {
      for (int c = 0; c < BLOCK_COLS; c++) {
          square[i][c] = data[i + (BLOCK_ROWS *c)];

      }
    }
}

/**
 * This function rearranges a 4 × 4 arrangement of data values, returning them 
 * as a one-dimensional array of 16 values.
 * @param data 16-byte array that will be filled with the rearranged data values
 * @param square 4x4 array representing the current AES state 
 */
void squareToBlock( byte data[ BLOCK_SIZE ], byte const square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {
  for (int i = 0; i < BLOCK_ROWS; i++) {
      for (int col = 0; col < BLOCK_COLS; col++) {
          data[i + (BLOCK_ROWS * col)] = square[i][col];

      }
  }
}

/**
 * This function performs the shiftRows operation on the given 4 × 4 square of values.
 * @param square 4x4 array representing the current AES state
 */
void shiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {
  //a e i m
  //b f j n
  //c g k o
  //d h l p

  //shift row 0 left by 0
  //shift row 1 left by 1
  //shift row 2 left by 2
  //shift row 3 left by 3

  //a e i m
  //f j N b
  //k o c g
  //p d h l

  ////shift row 1 left by 1
    
  //b f j n  ->  F j n b 
  //2nd row (index 1)
  byte tone = square[1][0]; //b 
  square[1][0] = square[1][1]; //b = f
  square[1][1] = square[1][2]; //f = j
  square[1][2] = square[1][3];        
  square[1][3] = tone;

  //c g k o  ->  k o c g
  //shift row 2 left by 2
  byte ttwo = square[2][0]; //c
  byte ttwo1 = square[2][1]; //g
  square[2][0] = square[2][2]; //c = k
  square[2][1] = square[2][3]; //g = o
  square[2][2] = ttwo; //k = c
  square[2][3] = ttwo1; //o = g 

  //d h l p  ->  p d h l
  //shift row 3 left by 3
  byte tthree = square[3][3]; //p
  square[3][3] = square[3][2]; //p = l    
  square[3][2] = square[3][1]; //l = h
  square[3][1] = square[3][0]; //h = d
  square[3][0] = tthree; //d = p      

}

/**
 * This function performs the inverse shiftRows operation on the given 4 × 4 square of values.
  * @param square 4x4 array representing the current AES state
 */
void unShiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {
  //a e i m
  //f j N b
  //k o c g
  //p d h l

  //a e i m
  //b f j n
  //c g k o
  //d h l p

  //row 1  f j n b  ->  b f j n
  byte tone = square[1][3]; //b
  square[1][3] = square[1][2]; //b = n
  square[1][2] = square[1][1]; //n = j      
  square[1][1] = square[1][0];
  square[1][0] = tone;
    
  //row 2 right by 2
  byte ttwo = square[2][3]; //g
  byte ttwo1 = square[2][2]; //c
  square[2][3] = square[2][1]; //g = o
  square[2][2] = square[2][0]; //c = k    
  square[2][1] = ttwo1; //o = c
  square[2][0] = ttwo; //k = g
    
  //row 3 right by 3
  byte tthree = square[3][0]; //d
  square[3][0] = square[3][1]; //d = p    
  square[3][1] = square[3][2]; //p = h  
  square[3][2] = square[3][3]; //h = l
  square[3][3] = tthree; //l = d



}

/**
 * This function performs the mixColumns operation on the given 4 × 4 square of values, multiplying each column by the matrix shown in the requirements section.
  * @param square 4x4 array representing the current AES state
 */
void mixColumns(byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {
  //multiply by forward matrix

  byte result[ BLOCK_ROWS ][ BLOCK_COLS ];

  for (int i = 0; i < BLOCK_COLS; i++) {
    for (int j = 0; j < BLOCK_ROWS; j++) {

              
      byte one = fieldAdd(fieldMul(forwardMixMatrix[j][0], square[0][i]), fieldMul(forwardMixMatrix[j][1], square[1][i]));
      byte one1 = fieldAdd(fieldMul(forwardMixMatrix[j][2], square[2][i]), fieldMul(forwardMixMatrix[j][3], square[3][i]));
      
      byte rount = fieldAdd(one, one1);  
            
      result[j][i] = rount;
  


    }


    }
    //copy result back to square
    for (int r = 0; r < BLOCK_ROWS; r++){
      for (int c = 0; c < BLOCK_COLS; c++) {
          square[r][c] = result[r][c];
      }
    }
  
}


/**
 * This function performs the inverse of the mixColumns operation on the given 4 × 4 square of values, 
 * multiplying each column by the inverse of the mixColumns matrix shown in the requirements section.
 * @param square 4x4 array representing the current AES state
 */
void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] ) {
  
  
  byte result[ BLOCK_ROWS ][ BLOCK_COLS ];

  for (int i = 0; i < BLOCK_COLS; i++) {
    for (int j = 0; j < BLOCK_ROWS; j++) {

      //multiply by inverse matrix
      byte one = fieldAdd(fieldMul(inverseMixMatrix[j][0], square[0][i]), fieldMul(inverseMixMatrix[j][1], square[1][i]));
      byte one1 = fieldAdd(fieldMul(inverseMixMatrix[j][2], square[2][i]), fieldMul(inverseMixMatrix[j][3], square[3][i]));
      
      byte rount = fieldAdd(one, one1);  
            
      result[j][i] = rount;
   

    }


    }
    //copy result back to square
    for (int r = 0; r < BLOCK_ROWS; r++){
      for (int c = 0; c < BLOCK_COLS; c++) {
          square[r][c] = result[r][c];
      }
    }

}


/**
 * This function encrypts a 16-byte block of data using the given key. 
 * It generates the 11 subkeys from key, adds the first subkey, then performs the 10 rounds of operations needed to encrypt the block.
 * @param data 16-byte array representing the current AES state
 * @param key 16-byte AES key used to encrypt the data
 */
void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {

}

/**
 * This function decrypts a 16-byte block of data using the given key. 
 * It generates the 11 subkeys from key, then performs the 10 rounds of inverse operations (and then an addSubkey) to decrypt the block.
 * @param data 16-byte array representing the current AES state
 * @param key 16-byte AES key used to decrypt the data
 */
void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {

}
