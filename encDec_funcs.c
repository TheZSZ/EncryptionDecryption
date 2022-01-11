// Zeeshan Khan
// Encryption Decryption Functions
// 1/10/2022

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "encDec_funcs.h"

void parseArgs(int argc, char *argv[], char **file, char **o, char **k) {
	// Errnum checks amount of stderr and count is for stderr 201
	int errnum = 0; int count = 0; bool a = false;	// bool to see if successful
	for(int i = 0; i < argc; i++) {
		// help arg passes
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-help") == 0) {
			help();	//help message
		}
		// input arg passed
		if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-input") == 0) {
			if((i+1) < argc) {
				// checks if -o or -k after (to make sure not last thing entered)
				if(strcmp(argv[i+1], "-o") == 0 || strcmp(argv[i+1], "--output") == 0 || strcmp(argv[i+1], "-output") == 0 || strcmp(argv[i+1], "-k") == 0 || strcmp(argv[i+1], "--key") == 0 || strcmp(argv[i+1], "-key") == 0) {
					fprintf(stderr, "command line error (203): no argument after '-i|--input'\n");
					errnum += 1; exit(203);
				} else {
					*file = argv[i+1]; count += 1; 
					a = true;
				}
			} else {
				fprintf(stderr, "command line error (203): no argument after '-i|--input'\n"); exit(203);
			}			
		}
		// output arg passed
		if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-output") == 0) {
			if((i + 1) < argc) {
				// checks if -k or -i after (to make sure not last thing entered)
				if(strcmp(argv[i+1], "-k") == 0 || strcmp(argv[i+1], "--key") == 0 || strcmp(argv[i+1], "-key") == 0 || strcmp(argv[i+1], "-i") == 0 || strcmp(argv[i+1], "--input") == 0 || strcmp(argv[i+1], "-input") == 0) {
					fprintf(stderr, "command line error (204): no argument after '-o|--output'\n");
					errnum += 1; exit(204);
				} else {
					*o = argv[i+1];	count += 1;
					a = true;
				}
			} else {
				fprintf(stderr, "command line error (204): no argument after '-o|--output'\n"); exit(204);
			}
		}
		// key arg passed
		if(strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0 || strcmp(argv[i], "-key") == 0) {
			if((i + 1) < argc) {
				// checks if -i or -o after (to make sure not last thing entered)
				if(strcmp(argv[i+1], "-i") == 0 || strcmp(argv[i+1], "--input") == 0 || strcmp(argv[i+1], "-input") == 0 || strcmp(argv[i+1], "-o") == 0 || strcmp(argv[i+1], "--output") == 0 || strcmp(argv[i+1], "-output") == 0) {
					fprintf(stderr, "command line error (205): no argument after '-k|--key'\n");
					errnum += 1; exit(205);
				} else {
					*k = argv[i+1];	count += 1; 
					a = true;
				}
			} else {
				fprintf(stderr, "command line error (205): no argument after '-k|--key'\n"); exit(205);
			}
		}
	}
	if(errnum == 1) {
		exit(205);
	}
	if(argc != 7 && a) {
		fprintf(stderr, "command line error (202): one or more required arguments not entered\n");
		exit(202);
	} else if (count < 3) {
		fprintf(stderr, "command line error (201): incorrect/unexpected argument entered\n");
		exit(201);
	}
}

// Creates a memory allocation
void *Malloc(size_t bytes) {
  void *ptr = NULL;
  if((ptr = malloc(bytes)) == NULL) {
    fprintf(stderr, "Could not allocate space %d - %s\n", errno, strerror(errno));
    //exit(99);                                                            
  }
  return(ptr);
}

// Opens a given file
FILE *Fopen(const char *file, const char *mode) {
	FILE *fp = fopen(file, mode);
	if (fp == NULL) {
		fprintf(stderr, "File not found %d - %s. Try checking your paths.\n", errno, strerror(errno));
		exit(2);
	}
	return(fp);
}

// Reads a given file key
void readKey(unsigned char *ptr, size_t length, FILE *key) {
	size_t a = Fread(ptr, sizeof(char), length, key);
	if(a < length) {
		fprintf(stderr, "Readkey error (206): key is a fewer bytes than expected (%zu vs. %zu)\n", a, length);
		exit(206);
	}
}

// Encryption / Decryption XOR
void encryptDecrypt(unsigned char *ptr, unsigned char *keyptr, size_t size, FILE *inputF, FILE *outF) {
	size_t a = 0; size_t b = 0;
	while((a = Fread(ptr, sizeof(char), size, inputF)) != 0) {
		if(a < size) {
			size = a;
		}
		for(size_t i = 0; i < size; i++) {
			ptr[i] = ptr[i] ^ keyptr[i];
		}
		b = Fwrite(ptr, sizeof(char), size, outF);
		if(b != a) {
			fprintf(stderr, "encrypt/decrypt error (207): unable to write all items read (%zu vs. %zu)\n", b, a);
			exit(207);
		}
	}
}

// Fread method: Reads a file
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t a = fread(ptr, size, nmemb, stream);
	if(ferror(stream) && !feof(stream)) {
		fprintf(stderr, "Fread Error %d - %s\n", errno, strerror(errno));
	}
	return a;
}

// Fwrite method: Writes to a file
size_t Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	if(fwrite(ptr, size, nmemb, stream) != nmemb) {
		fprintf(stderr, "Fwrite Error %d - %s\n", errno, strerror(errno));
	}
	return nmemb;	
}

// Fclose method: closes a file 
void Fclose(FILE *ptr) {
	if(ptr != NULL) {
		fclose(ptr); ptr = NULL;
	} else {
		fprintf(stderr, "Fclose Error %d - %s\n", errno, strerror(errno)); exit(errno);
	}
}

// Help method: prints out a helpful message
void help() {
	printf("\n\t#######################################################################################\n\t# encDec performs an XOR-based encryption/decryption on the specified input file      #\n\t# using the specified key file to produce the specified output file.\t\t      #\n\t# Usage: encDec -i|--input <input file> -o|--output <output file> -k|--key <key file> #\n\t#######################################################################################\n\n");
	exit(0);
}
