#pragma once
struct Pixel {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};



struct MainHeader {
	unsigned char sig[2];
	unsigned int size;
	unsigned int reserved;
	unsigned int offset;
};


struct InfoHeader {
	unsigned int width;
	unsigned int height;

	unsigned short planes;

	unsigned short bitsperpixel;

	unsigned int compression;

	unsigned int datasize;

	unsigned int resx;

	unsigned int resy;


	unsigned int numcolours;
};

struct ImageData {
	unsigned int width;
	unsigned int height;

	char *data;
};

ImageData* loadFile(char* filename);
