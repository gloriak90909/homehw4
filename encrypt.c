/**
 * @file encrypt.c
 * @author Gloria Kim
 * This is the main component for the encrypt program. 
 * It contains the main function and uses the other components to read the input file, 
 * to perform AES encryption and to write out the ciphertext output.
 */

#include <stdlib.h>
#include <stdio.h>
#include "aes.h"
#include "io.h"
#include "field.h"
#include "aesUtil.h"

int main(int argc, char *argv[]) {

  //./encrypt key-01.txt plain-01.txt cipher-output.bin

  //check if correct number of arguments
  if (argc != 4) {
    fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }


  //READ KEY FILE args[1]
  int keyLength;

  byte *key_input = readBinaryFile(argv[1], &keyLength );
  //if keyLength is not 16 bytes, error
  if (keyLength != BLOCK_SIZE) {
    fprintf(stderr, "Bad key file: %s\n", argv[1]);
    exit(1);
  }


  //READ PLAINTEXT INPUT FILE args[2]
  int inputLength;
  byte *plaintext_input = readBinaryFile(argv[2], &inputLength);

  if (inputLength <= 0) {
    fprintf(stderr, "Bad plaintext file length: %s\n", argv[2]);
    exit(1);
  }

  if (inputLength % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad plaintext file length: %s\n", argv[2]);
    exit(1);
  }


  //ALLOCATE CIPHERTEXT OUTPUT ARRAY
  byte *cipher_input = (byte *)malloc(inputLength * sizeof(byte));
  if (cipher_input == NULL) {
    fprintf(stderr, "Allocation error for ciphertext\n");
    exit(1);
  }

  //ENCRYPT EACH BLOCK
  for (int i = 0; i < inputLength / BLOCK_SIZE; i++){
    
    encryptBlock(&plaintext_input[i * BLOCK_SIZE], key_input);
    
    for (int k = 0; k < BLOCK_SIZE; k++) {
      cipher_input[(i * BLOCK_SIZE) + k] = plaintext_input[(i * BLOCK_SIZE) + k];

    }
  }

  //WRITE CIPHERTEXT OUTPUT FILE args[3]
  writeBinaryFile(argv[3], cipher_input, inputLength );


  free(key_input);
  free(plaintext_input);
  free(cipher_input);

  return 0;





}

