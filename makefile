# Zeeshan Khan
# Encryption Decryption makefile
# 1/10/2022

LFLAGS = -g
CFLAGS = -g -c -Wall -Wextra -Wwrite-strings

encDec: encDec.o encDec_funcs.o
	gcc $(LFLAGS) encDec.o encDec_funcs.o -o encDec

encDec.o: encDec.c
	gcc $(CFLAGS) encDec.c -o encDec.o

encDec_funcs.o: encDec_funcs.c
	gcc $(CFLAGS) encDec_funcs.c -o encDec_funcs.o

encDec.c:
	echo "making" > encDec.c

encDec_funcs.c:
	echo "making funcs" > encDec_funcs.c

clean:
	rm -f *.o
	rm -f encDec