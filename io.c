/**
 * @file io.c
 * @author Gloria Kim
 * This component implements input/output functions for the AES encryption and decryption algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "field.h"
#include "io.h"

/**
 * This function reads the contents of the binary file with the given name. 
 * It returns a pointer to a dynamically allocated array of bytes containing the entire file contents. 
 * The size parameter is an integer that’s passed by reference to the function. 
 * The function fills in this integer with the total size of the file (i.e., how many bytes are in the returned array).
 * @param filename name of the file to read.
 * @param size pointer to an integer that will be filled with the size of the file.
 * @return pointer to a dynamically allocated array of bytes containing the file contents.
 */
byte *readBinaryFile( char const *filename, int *size ) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        fprintf(stderr,"Can't open file: %s\n", filename);
        exit(1);
    }

    //find the length of the file
    //seek returns 0 if it successfully moves to the end
    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr,"Error seeking to end of file: %s\n", filename);
        fclose(fp);
        exit(1);
    }

    //ftell returns a long
    long length = ftell(fp);
    if (length < 0) {
        fprintf(stderr,"Length error: %s\n", filename);
        fclose(fp);
        exit(1);
    }

    rewind( fp );

    //converts long to int
    *size = (int)length;
     
    //check for error length in other classes

    //dynamically allocate array of bytes
    byte *list = (byte *)malloc(length * sizeof(byte));
    //check if malloc worked
    if (list == NULL) {
        fprintf(stderr, "Memory allocation error for file: %s\n", filename);
        fclose(fp);
        exit(1);
    }

    //read file into the byte array
    int numElementsRead = fread(list, 1, length, fp);

    //check if fread read the correct number of elements
    if (numElementsRead != length) {
        fprintf(stderr, "Error reading in fread: %s\n", filename);
        free(list);
        fclose(fp);
        exit(1);
    }

    fclose(fp);

    return list;

}


/**
 * This function writes the contents of the given data array (in binary) to the file with the given name. 
 * The size parameter says how many bytes are contained in the data array.
 * @param filename name of the file to write.
 * @param data pointer to the array of bytes to write.
 */
void writeBinaryFile( char const *filename, byte *data, int size ) {
    FILE *dest = fopen(filename, "wb");

    if (dest == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(1);
    }
   
    int elementsWritten = fwrite(data, 1, size, dest);
    if (elementsWritten != size) {
        fprintf(stderr, "Error writing to file: %s\n", filename);
        fclose(dest);
        exit(1);
    }

    fclose(dest);
}
