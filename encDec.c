// Zeeshan Khan
// Encryption Decryption Main File
// 1/10/2022

#define BLOCKSIZE 16

#include <stdio.h>       /* for fprintf, sprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* error handling */
#include <string.h>      /* for strings */
#include "encDec_funcs.h"

/* compile with: make */

int main(int argc, char *argv[]) {
	char *ifile = NULL;               /* to point to input file name */
	FILE *fip = NULL;                 /* to point to opened input file */
	char *ofile = NULL;               /* to point to output file name */
	FILE *fop = NULL;                 /* to point to opened output file */
	char *kfile = NULL;               /* to point to key file name */
	FILE *fkp = NULL;                 /* to point to opened key file */
	unsigned char block[BLOCKSIZE];   /* to hold bytes read from input file */
	unsigned char key[BLOCKSIZE];     /* to hold key for encryption/decryption read from key file */
  
  	if(argc == 1) {					  /* if no args but encDec */
		printf("\nTry 'encDec --help' for more information.\n\n");
		exit(0);
	}
  
	parseArgs(argc, argv, &ifile, &ofile, &kfile);    /* parse arguments and return pointers to filenames */  
	fip = Fopen(ifile, "r");
	fop = Fopen(ofile, "w");
	fkp = Fopen(kfile, "r");
	readKey(key, BLOCKSIZE, fkp);                     /* read the key for encryption/decryption */
	encryptDecrypt(block, key, BLOCKSIZE, fip, fop);  /* encrypt/decrypt the input file and write to output file */
	Fclose(fip);
	Fclose(fop);
	Fclose(fkp);
	return 0;
}