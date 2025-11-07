/**
 * @file field.h
 * @author Gloria Kim
 * This component implements support for basic arithmetic operations in an 8-bit (a byte) Galois field.
 * 
 */

#include "field.h"

 /**
 * This function reads the contents of the binary file with the given name. 
 * It returns a pointer to a dynamically allocated array of bytes containing the entire file contents. 
 * The size parameter is an integer that’s passed by reference to the function. 
 * The function fills in this integer with the total size of the file (i.e., how many bytes are in the returned array).
 * @param filename name of the file to read.
 * @param size pointer to an integer that will be filled with the size of the file.
 */
byte *readBinaryFile( char const *filename, int *size );


/**
 * This function writes the contents of the given data array (in binary) to the file with the given name. 
 * The size parameter says how many bytes are contained in the data array.
 * @param filename name of the file to write.
 * @param data pointer to the array of bytes to write.
 */
void writeBinaryFile( char const *filename, byte *data, int size );
