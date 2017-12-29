// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Main.h"
#include "stdafx.h"
#include "FileHandling.h"
#include "SHA.h"
#include "AES.h"
#include <iostream>
using namespace std;


void displayIntro() {
	printf("\nWELCOME\n\n");

}

void printHex(unsigned char* data, unsigned int len) {
	for (int i = 0; i< len; i++) {
		printf("%x", data[i]);
	}
	printf("\n");
}



void decryptFile() {



}

void encryptFile() {


}


int main() {
	displayIntro();





	printf("Do you want to Encrypt or Decrypt?                (e or d)\n");
	char mode = 'a';//getchar();// getchar();
	scanf_s(" %c", &mode, 1);
	
	while (mode != 'e' && mode != 'd') {
		printf("please enter either e or d\n");
		scanf_s(" %c", &mode, 1);
	}
	
	printf("launch BMP creation tool?                          (y or n)\n");
	char in = 'a';
	scanf_s(" %c", &in, 1); 
	//validate response
	in = tolower(in);
	while (in != 'y' && in != 'n') {
		printf("please enter either y or n\n");
		scanf_s(" %c", &in, 1);
		in = tolower(in);
	}

	if (in == 'y') {
		printf("Remember to save the file as a 24 bit colour BMP!\n");
		system("\%windir\%\\system32\\mspaint.exe");
	}


	//get filename
	char fname[100];
	printf("enter filename of bitmap to use as key (max 100 characters)\n");
	scanf_s(" %s", fname, 100);
	//======================================
	
	
	//ask if delete file
	printf("delete file after use?                          (y or n)\n");
	in = 'a';
	scanf_s(" %c", &in, 1);
	in = tolower(in);

	//validate response
	while (in != 'y' && in != 'n') {
		printf("please enter either y or n\n");
		scanf_s(" %c", &in, 1);
		in = tolower(in);
	}

	//LOAD IMAGE DATA

	ImageData* image = loadFile(fname);

	if (image == NULL) {
		printf("error loading image, quitting\n");
		getchar();
		getchar();
		
		return -1;
		
	}

	//PASS TO FORMAT FUNCTION (OPTIONAL)

	//extract pixels into single char buffer
	char * pixelBuffer = image->data;


	int height = image->height;
	int width = image->width;

	//check buffer created correctly
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int i = 0; i < 3; i++) {
				printf("%x", pixelBuffer[(y*height) + (x * 3) + i]);
			}
		}
	}
	//HASH DATA
	printf("/n");
	
	unsigned char* digest = (getHash(pixelBuffer, 256));



	//DELETE AFTER HASH (helps prevent deletion being cancelled if program is killed before gets to end):
	if (tolower(in) == 'y') {
		if (remove(fname) == 0) {
			printf("file %s removed successfully", fname);
		}
		else {
			printf("error deleting key, make sure you do this manually or key could be reused");
		}
	}


	unsigned char iv[CryptoPP::AES::BLOCKSIZE] = "13456789101112";
	if (mode == 'e') {
		//encrypt file
		char* something = "asd";
		encrypt(something, digest, iv);

	} else if (mode == 'd'){
		//decrypt file
		char* something = "asd";
		decrypt(something,digest, iv);
	} 



	//HASH
	//printf(encrypt("abcdefghijklmnop", 16));
	//unsigned char* hash = (encrypt("abc", 3));
	
	//unsigned char* hash = (encrypt("abc", 3));

	printf("finished\n");
	getchar();
	getchar();
	
    return 0;
}



