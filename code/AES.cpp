#include "stdafx.h"

#include <stdio.h>
#include <iomanip>

// sooooo
// because I found the libs hard to install (remember this is my first real C project) I kind of just dumped the lib folder on my desktop and linked the headers
// It would probably be better if I redid the whole library used
// I've heard OpenSSL is very good


#include <C:\Users\XXX\Desktop\cryptopp565\dll.h>
#include <C:\Users\XXXX\Desktop\cryptopp565\modes.h>
#include <C:\Users\XXX\Desktop\cryptopp565\aes.h>
#include <C:\Users\XXX\Desktop\cryptopp565\filters.h>
#include "AES.h"


void encrypt(char * text, unsigned char key[32], unsigned char iv[CryptoPP::AES::BLOCKSIZE]) {
	printf("ENCRYPTING\n");
	std::string plaintext(text);
	std::string ciphertext;
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
	stfEncryptor.MessageEnd();

	//
	// Dump Cipher Text
	//
	printf("Cipher Text: %d unsigned chars)", ciphertext.size());

	for (int i = 0; i < ciphertext.size(); i++) {

		printf("%x\n", (0xFF & static_cast<unsigned char>(ciphertext[i])));
	}

	printf("ciphertext: %s\n", ciphertext);



	printf("decrypt?  (y or n)\n");
	
	char in = 'a';
	scanf_s(" %c", &in, 1);
	in = tolower(in);

	//validate response
	while (in != 'y' && in != 'n') {
		printf("please enter either y or n\n");
		scanf_s(" %c", &in, 1);
		in = tolower(in);
	}

	if (in == 'y') {
		decrypt(ciphertext, key, iv);
	}
}


void decrypt(std::string ciphertext, unsigned char key[32], unsigned char iv[CryptoPP::AES::BLOCKSIZE]) {
	std::string decryptedtext;
	printf("DECRYPTING\n");
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
	stfDecryptor.MessageEnd();

	//
	// Dump Decrypted Text
	//
	std::cout << "Decrypted Text: " << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl << std::endl;



}

void test() {

	//Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-   
	//bit). This key is secretly exchanged between two parties before communication   
	//begins. DEFAULT_KEYLENGTH= 16 unsigned chars
	unsigned char key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
	char * plaintext = "PLAINTEXT";
	//std::string ciphertext = encrypt(plaintext, key, iv);
	//decrypt(ciphertext, key, iv);


	getchar();

}
