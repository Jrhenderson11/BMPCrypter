#include <stdio.h>
#include <iostream>
#include "stdafx.h"
#include "FileHandling.h"
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

ImageData* loadFile(char* filename) {

	printf("file: %s\n", filename);

	FILE* picture;
	fopen_s(&picture, filename, "rb");

	//NULL IF ERROR

	if (picture == NULL) {
		printf("error opening file (file does not exist)\n");
		return NULL;
	}

	// to seek:
	//fseek(picture, offset, SEEK_CUR / SEEK_SET);

	//to read:
	//fread(ptr, elementsize, num-elements, picture);
	MainHeader header;
	//=========================== MAIN HEADER =========================== \\

	fread(&header.sig, 2, 1, picture);
	fread(&header.size, sizeof(unsigned int), 1, picture);
	fread(&header.reserved, sizeof(unsigned int), 1, picture);
	fread(&header.offset, sizeof(unsigned int), 1, picture);

	// VALIDATE HEADER
	//put this in multiple lines because I prefer that too one massive unreadable one
	if (header.sig[0]!='B' || header.sig[1]!='M') {
		printf("error opening file (invalid header signature)\n");
		return NULL;
	}
	if (header.offset >= header.size) {
		printf("error opening file (invalid header offset)\n");
		return NULL;
	}

	//test 

	printf("sig: %c%c\n", header.sig[0], header.sig[1]);
	printf("size: %d\n", header.size);
	printf("offset: %d\n", header.offset);

	//=========================== INFO HEADER =========================== \\
	//has to be read manually

	//size (4)

	//this determines type of header
	unsigned int infosize;
	fread(&infosize, sizeof(int), 1, picture);

	printf("size: %d\n", infosize);

	if (infosize != 40) {
			printf("error opening file (file must have correct INFOHEADER)\n");
			return NULL;
	} else {
		InfoHeader info;
		fread(&info, sizeof(InfoHeader), 1, picture);

		unsigned int skipbits = (4 - ((info.width * 3) % 4));
		if (info.bitsperpixel != 24) {
			printf("non-compatible image: must have 24 bits-per-pixel\n");
			return NULL;
		}
		if (header.offset > (header.size-((info.width*3 +skipbits)*info.height))) {
			printf("error opening file (offset / size)\n");
			return NULL;
		}
		//DISPLAY

		printf("width: %d\n", info.width);
		printf("height: %d\n", info.height);

		printf("planes: %d\n", info.planes);
		printf("bits-per-pixel: %d\n", info.bitsperpixel);

		printf("compression: %d\n", info.compression);
		printf("datasize: %d\n", info.datasize);
		printf("num colours: %d\n", info.numcolours);
		
	//copy struct info into local for ease of use
	unsigned int width = info.width;
	unsigned int height = info.height;
		

	printf("skipbits: %d\n", skipbits);
	//seek to data offset
	fseek(picture, header.offset, SEEK_SET);
	
	//read data into array
	Pixel **pixels = new Pixel*[width];
	for (int i = 0; i< width ; i++) {
		pixels[i] = new Pixel[height];
	}

	//read in
	for (int y = 0; y< height; y++) {
		//pixels[x][y]
		for (int x = 0; x < width; x++) {
			fread(&pixels[x][y], sizeof(Pixel), 1, picture);
			printf("%x  %x  %x\n", pixels[x][y].blue, pixels[x][y].green, pixels[x][y].red);
		}
		fseek(picture, skipbits, SEEK_CUR);
	}
	fclose(picture);
	//consruct final struct and return
	ImageData image;// = (ImageData)malloc(sizeof(ImageData));
	image.width = width;
	image.height = height;

	char * pixelBuffer = (char*) calloc(width * height , sizeof(Pixel));
	//int height = image.height;
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = (y * (height)) + (x * 3);

			pixelBuffer[index] = pixels[x][y].blue;
			pixelBuffer[index + 1] = pixels[x][y].green;
			pixelBuffer[index + 2]= pixels[x][y].red;
		}
	}

	image.data = pixelBuffer;

	return &image;
	}
	// if conditions not met and somehow hasnt been caught

	printf("error opening file (unknown)\n");
	return NULL;
}
