/**
 * @file decrypt.c
 * @author Gloria Kim
 * This is the main component for the decrypt program. 
 * It contains the main function and uses the other components to read the input file, 
 * to perform AES decryption and to write out the plaintext output.
 */

#include <stdlib.h>
#include <stdio.h>
#include "aes.h"
#include "io.h"
#include "field.h"
#include "aesUtil.h"

int main(int argc, char *argv[]) {

  //$ ./decrypt key-01.txt cipher-output.bin plain-output.txt

  //check if correct number of arguments
  if (argc != 4) {
    fprintf(stderr, "usage: decrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }

  //read key file
  int keyLength;
  byte *keydata = readBinaryFile(argv[1], &keyLength );
  //if keyLength is not 16 bytes, error
  if (keyLength != BLOCK_SIZE) {
    fprintf(stderr, "Bad key file: %s\n", argv[1]);
    exit(1);
  }

  //read ciphertext input file
  int inputLength;
  byte *inputdata = readBinaryFile(argv[2], &inputLength);

  if (inputLength <= 0) {
    fprintf(stderr, "error reading inputfile: %s\n", argv[2]);
    exit(1);
  }
  if (inputLength % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad ciphertext file length: %s\n", argv[2]);
    exit(1);
  }

  //allocate plaintext output array
  byte *plaindata = (byte *)malloc(inputLength * sizeof(byte));
  if (plaindata == NULL) {
    fprintf(stderr, "Memory allocation error for plaintext output\n");
    exit(1);
  }
  //decrypt each block
  for (int i = 0; i < inputLength / BLOCK_SIZE; i++)
  {
    decryptBlock(&inputdata[i * BLOCK_SIZE], keydata);
    //copy decrypted block to plaindata
    for (int j = 0; j < BLOCK_SIZE; j++) {
      plaindata[i * BLOCK_SIZE + j] = inputdata[i * BLOCK_SIZE + j];
    }
  }
  //write plaintext output file
  writeBinaryFile( argv[3], plaindata, inputLength );

  


  return 0;
}