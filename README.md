# EncryptionDecryption
A program to encrypt and decrypt a plain text file in C

NOTE: Written on Linux

To compile the code, use the makefile by typing "make" in the directory.
![Screenshot](images/make.png)

You can encrypt the data in a file (with any filetype ending) by typing: <br />
```encDec -i [input file] -o [output file] -k [encryption key]```. <br />
The order of the input file (-i), output file (-o) and key file (-k) can be specified in any order. The output file does not need to exist, it will be made when the program is successfully run. <br />
For example, I pass through the file ```input.dec``` with the name of the output file I want (which the program creates) and a key file (key.bravo).
![Screenshot](images/enc.png)
As you can see, the output file, ```input.enc``` is different from ```input.dec```.

W.I.P
