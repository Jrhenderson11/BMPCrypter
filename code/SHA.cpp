
#include "stdafx.h"
#include "SHA.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

bool debugRotate = false;

unsigned char* getHash(char *rawData, unsigned long len) {
	
	
	printf("Data: \n");
	printf(rawData);
	printf("\n");
	unsigned long origLen = len;

	//init values (hex)
	unsigned int h[] = { 0x6a09e667 , 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
		
		
	unsigned int k[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

	};
	
	//64!!!!
	//(512 - (len+1+64 mod 512) mod 512)

	//prep message


	unsigned long bitLen = len * 8;
	unsigned long fullsize = (bitLen +65+ (512 - ((bitLen + 1 + 64) % 512) % 512) ) /8;

	char* data = (char*) calloc(fullsize, 1);
	printf("size of data: %d\n", fullsize);


	memcpy(data, rawData, len);

	printf("Data after copying: \n");
	printf(data);
	printf("\n");

	//append char to buffer
	data[len] = (1 << 7);
	len++;

	//pad data with 0's
	for (unsigned int i = len+15; i< fullsize; i++) {
		data[len] = 0;
		len++;
	}
	printf("data pointer: %p\n", (data));
	printf("padded data: \n");

	for (unsigned int i = 0; i < fullsize; i++) {
		printf_s("%x", data[i], 1);
	}
	//printf_s(data, fullsize);
	printf("\n");
	
	//COPY LEN TO THE END OF data



	//64 bit
	//HERE WE GO BASTERDS

	//// add length (in bits) into final pair of 32-bit integers (big-endian) [§5.1.1]
	//// note: most significant word would be (len-1)*8 >>> 32, but since JS converts
	//// bitwise-op args to 32 bits, we need to simulate this by arithmetic operators
	unsigned int lenHi = (bitLen) >>8;
	unsigned int lenLo = (bitLen) >> 0;
	
	printf("append: %d\n", bitLen);
	data[fullsize-2] = floor(lenHi);
	data[fullsize - 1] = lenLo;




	printf("len: %x\n", bitLen);
	printf("padded data + len: \n");
	//printf_s(data, fullsize);
	for (unsigned int i = 0; i < fullsize; i++) {
		printf_s("%x", data[i], 1);
	}
	printf("\n");

	



	//split into chunks

	unsigned int numChunks = (fullsize / 64);
	unsigned char **chunks = new unsigned char*[numChunks];

	for (unsigned int i = 0; i< numChunks; i++) {
		
		//creates a chunk of 512 bits (64 bytes)
		chunks[i] = new unsigned char[64]; // TICK
		memcpy(chunks[i], (&data[64*i]), 64);



		printf("chunk after copying: \n");
		for (int count = 0; count < 64; count++) {
			printf_s("%x", chunks[i][count], 1);
		}
		printf("\n");
	}

	//TEST
	
	
	//process chunks
	for (unsigned int cNum = 0; cNum < numChunks; cNum++) {


		//create words array and 0
		unsigned int* words = (unsigned int*) calloc(64,8);
		for (int count = 0; count < 16; count++) {
			printf_s("words when intialized: %d\n", words[count], 1);
		}
		printf("\n");

		printf("start copying chunks\n");
		printf("chunk I am copying:\n");
		//copy chunk into first 16 elements
		for (int count = 0; count < 64; count++) {
			printf_s("%x", chunks[cNum][count], 1);
		}
		printf("\n");
		//FLIP BEFORE COPYING

		unsigned char** flipped = (unsigned char**) calloc(sizeof(char*), 16);

		for (int i=0;i<16;i++) {
			flipped[i] = (unsigned char*) calloc(1, 4);
		}
		
		printf("size of data: %d\n", fullsize);
	//===============================================================================
		for (unsigned int i = 0; i < 64; i+=4) {
			unsigned int findex = i / 4;

			//chunks i-i+4
			unsigned char* word = (unsigned char*) calloc(4, 1);
			unsigned char* revword = (unsigned char*)calloc(4, 1);
			memcpy(word, &chunks[cNum][i], 4);
			for (int count = 3; count > -1;count--) {
				int forwards = 3 - count;
				unsigned char letter = word[count];
				revword[forwards] = letter;
			}
			//copy word backward into flipped


			/*printf("word : ");
			displayBinC(word, 4);*/


			memcpy(flipped[findex], revword, 4);
			
			
		}
		
		//============================================================================================
		//print flipped
		printf("flipped after copied from chunk\n", fullsize);
		for (int i = 0; i<16; i++) {
			printf("flipped %d: ", i);
			displayBinC(flipped[i], 4);
		}
		printf("\n");
		printf("Chunk: ");
		displayBinC(chunks[cNum], 64);
		

		//transpose flipped into words THE CORRECT BLOODY WAY
		
		//OFC THIS IS FUCKING INSANE
		//these are bloody pointers u fucking moron
		//memcpy(words, flipped, 64);
		for (int count = 0; count < 16; count++) {
			memcpy(&words[count], flipped[count], 4);
		
		}










		
		printf("words after copying from flipped:\n");
		//CHECK
		//printf("chunk: %s", chunks[cNum]);

		//doesnt look right somehow
		for (int count = 0; count < 64; count++) {

			//printf_s("%x-", words[count], 4);
			printf("word[%d]: ", count);
			displayBin(words[count]);
		}
		
		printf("\n");




		//================================================================================= COULD BE HERE
		for (unsigned int i = 16; i< 64; i++) {

			
			unsigned int sigma0 = (rightRotate(words[i - 15], 7)) ^ (rightRotate(words[i - 15], 18)) ^ (words[i - 15] >> 3);
			printf("i: %d\n", i);

			/*printf("sigma0: %d\n", sigma0);
			displayBin(sigma0);*/
			printf("input: %d\n", words[i-2]);
			//displayBin(sigma1);


			unsigned int sigma1 = (rightRotate(words[i - 2], 17)) ^ (rightRotate(words[i - 2], 19)) ^ (words[i - 2] >> 10);
			printf("sigma1: %d\n", sigma1);
			displayBin(sigma1);



			words[i] = words[i - 16] + sigma0 + words[i - 7] + sigma1;
			//words[i] = words[i - 16] + sigma0 + sigma1;


		}

		unsigned int a = h[0];
		unsigned int b = h[1];
		unsigned int c = h[2];
		unsigned int d = h[3];
		unsigned int e = h[4];
		unsigned int f = h[5];
		unsigned int g = h[6];
		unsigned int HH = h[7];

		//compression loop 

		for (int i = 0; i < 64; i++) {

			unsigned int sum1 = (rightRotate(e, 6)) ^ (rightRotate(e, 11)) ^ (rightRotate(e, 25)); //CORRECT 
		
			unsigned int ch = (e & f) ^ ((~e) & g); //CORRECT
		
			unsigned int temp1 = HH + sum1 + ch + k[i] + words[i];

			unsigned int sum0 = (rightRotate(a, 2)) ^ (rightRotate(a, 13)) ^ (rightRotate(a, 22));

			unsigned int maj = (a & b) ^ (a & c) ^ (b & c);

			unsigned int temp2 = sum0 + maj;


			HH = g;
			g = f;
			f = e;
			e = d + temp1; //INCORRECT
			d = c;
			c = b;
			b = a; 
			a = temp1 + temp2; //INCORRECT
		
			printf("t: %d ", i);
			printf("a: %x ", a);
			printf("b: %x ", b);
			printf("c: %x ", c);
			printf("d: %x ", d);
			printf("e: %x ", e);
			printf("f: %x ", f);
			printf("g: %x ", g);
			printf("h: %x\n ", HH);
			//free(words);
		}


		//unsigned int h[] = { 0x6a09e667 , 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};


		h[0] += a;
		h[1] = h[1] + b;
		h[2] = h[2] + c;
		h[3] = h[3] + d;
		h[4] = h[4] + e;
		h[5] = h[5] + f;
		h[6] = h[6] + g;
		h[7] = h[7] + HH;

		
		
	}





	char* hash = (char*) malloc(256);
	
	for (int i = 0; i< 8;i++) {
		printf("%x\n", h[i]);
		unsigned int part = h[i];

		//concatenate each part of hash to form complete 
		sprintf_s(hash + (i * sizeof(unsigned int)), 32, "%x", part);
		//printf(hash);

		

	}

	printf("hash: %x\n", *hash);
	printf("\n");
	
	free(data);
	for (unsigned int i = 0; i < numChunks; i++) {
		free(chunks[i]);
	}
	free(chunks);
	
	//free(h);
	
	printf("returning\n");

	return (unsigned char*) hash;
}

unsigned int rightRotate(unsigned int arrCpy , unsigned int num) {
	unsigned int arr = arrCpy;
	//rotate arr right by num

	unsigned int ret = ((arr >> num) | (arr << (32 - num)));

	if (false&&debugRotate) {
		printf("====================\n");
		displayBin(arrCpy);
		printf("rotated %d:\n", num);
		displayBin(ret);
		printf("====================\n");
	}
	
	return ret;
}

//debugging functions
void displayBin(unsigned int n) {
	
	int k;
	for (int c=31;c>-1;c--) {
		k = n >> c;
		if (k & 1){
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf("\n");
}

void displayBinC(unsigned char* data, int len) { 

	int k;
	for (int counter = 0; counter < len; counter++) {
		for (int c = 7; c>-1; c--) {
			k = data[counter] >> c;
			if (k & 1) {
				printf("1");
			}
			else {
				printf("0");
			}
		}
		printf("-");
	}

	
	

	printf("\n");
}