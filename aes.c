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
  //10 rounds + inital key

  //round 0: original key
  //round 1: 16 bytes derived from key
  //roun 2: 16 bytes derived from round 1 key
  //...
  //round 10: 16 bytes derived from round 9 key

  //copying original key to round 0
  for (int i = 0; i < BLOCK_SIZE; i++) {
    subkey[0][i] = key[i];
  }

  for (int k = 1; k < ROUNDS + 1; k++) {
  //round 2
  byte word0[4] = {subkey[k-1][0], subkey[k-1][1], subkey[k-1][2], subkey[k-1][3]};
  //byte 4-7
  byte word1[4] = {subkey[k-1][4], subkey[k-1][5], subkey[k-1][6], subkey[k-1][7]};
  byte word2[4] = {subkey[k-1][8], subkey[k-1][9], subkey[k-1][10], subkey[k-1][11]};
  byte word3[4] = {subkey[k-1][12], subkey[k-1][13], subkey[k-1][14], subkey[k-1][15]};
  
  byte gfuncword[4];
  //dest, src, rountcount
  gFunction(gfuncword, word3, k); 

  byte gfuncWithW0[4];

  //g function xor with word0
  for (int i = 0; i < 4; i++) {
      gfuncWithW0[i] = word0[i] ^ gfuncword[i]; 
  }

  //puts gfuncWithW0 into subkey[k] first 4 bytes
  for (int i = 0; i < 4; i++) {
    subkey[k][i] = gfuncWithW0[i];
  }
  
  //word1 xor with subkey[k] first 4 bytes
  for (int i = 0; i < 4; i++) {
      subkey[k][i+4] =  subkey[k][i] ^ word1[i];
  }

  //word2 xor with subkey[k] second 4 bytes
  for (int i = 0; i < 4; i++) {
      subkey[k][i+8] = subkey[k][i+4] ^ word2[i];
  }

  //word3 xor with subkey[k] third 4 bytes
  for (int i = 0; i < 4; i++) {
      subkey[k][i+12] = subkey[k][i+8] ^ word3[i];
  }



  }

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
  square[2][1] = ttwo; //o = c
  square[2][0] = ttwo1; //k = g
    
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


void subBytes(byte data[BLOCK_SIZE]) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    data[i] = substBox(data[i]);
  }
}




/**
 * This function encrypts a 16-byte block of data using the given key. 
 * It generates the 11 subkeys from key, adds the first subkey, then performs the 10 rounds of operations needed to encrypt the block.
 * @param data 16-byte array of the plaintext that will be encrypted into ciphertext
 * @param key the original 16-byte AES key used to encrypt the data
 */
void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {
  // generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] ) {
  byte subkey[ROUNDS + 1 ][ BLOCK_SIZE ];

  generateSubkeys(subkey, key);  

  //mixes original key with the plaintext data before round1
  addSubkey(data, subkey[0]);

  byte square[ BLOCK_ROWS ][ BLOCK_COLS ];

  //subBytes
  //shiftRows
  //mixColumns
  //addSubkey
  for (int i = 0; i < ROUNDS -1; i++) {
    subBytes(data);
    blockToSquare(square, data);
    shiftRows(square);
    mixColumns(square);
    squareToBlock(data, square);
    addSubkey(data, subkey[i+1]);
    
    
  }

  //without MixColumns in the last round

  subBytes(data); 
  blockToSquare(square, data);
  shiftRows(square);
  squareToBlock(data, square);
  addSubkey(data, subkey[ROUNDS]);
  
}

/**
 * This function decrypts a 16-byte block of data using the given key. 
 * It generates the 11 subkeys from key, then performs the 10 rounds of inverse operations (and then an addSubkey) to decrypt the block.
 * @param data 16-byte array representing the current AES state
 * @param key 16-byte AES key used to decrypt the data
 */
void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] ) {

  byte subkey[ROUNDS + 1 ][ BLOCK_SIZE ];
  byte square[ BLOCK_ROWS ][ BLOCK_COLS ];

  addSubkey(data, subkey[10]);

  generateSubkeys(subkey, key);

  //round inverse operations 9 to 1
  for (int i = ROUNDS; i > 1; i--) {
    addSubkey(data, subkey[i]);
    squareToBlock(data, square);
    unShiftRows(square);
    blockToSquare(square, data);
    subBytes(data); 
    unMixColumns(square);
    squareToBlock(data, square);
  }


  //round 10 without MixColumns
  addSubkey(data, subkey[ROUNDS]);
  squareToBlock(data, square);
  shiftRows(square);
  blockToSquare(square, data);
  subBytes(data); 
  
  addSubkey(data, subkey[0]);
  
  
}
