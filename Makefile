# Compiler for the default rule to use.
CC= gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE -g
LDFLAGS = -lm

all: encrypt decrypt

encrypt: encrypt.o aes.o aesUtil.o io.o field.o
	$(CC) $(CFLAGS) -o encrypt encrypt.o aes.o aesUtil.o io.o field.o $(LDFLAGS)

decrypt: decrypt.o aes.o aesUtil.o io.o field.o
	$(CC) $(CFLAGS) -o decrypt decrypt.o aes.o aesUtil.o io.o field.o $(LDFLAGS)

encrypt.o: encrypt.c aes.h io.h aesUtil.h field.h
	$(CC) $(CFLAGS) -c encrypt.c

decrypt.o: decrypt.c aes.h io.h aesUtil.h field.h
	$(CC) $(CFLAGS) -c decrypt.c

io.o: io.c io.h field.h
	$(CC) $(CFLAGS) -c io.c

aes.o: aes.c aes.h aesUtil.h field.h
	$(CC) $(CFLAGS) -c aes.c

aesUtil.o: aesUtil.c aesUtil.h field.h
	$(CC) $(CFLAGS) -c aesUtil.c

field.o: field.c field.h
	$(CC) $(CFLAGS) -c field.c


clean:
	rm -f *.o encrypt decrypt