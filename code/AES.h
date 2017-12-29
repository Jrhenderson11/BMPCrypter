#pragma once

//get headers from library for cryptoPP stuff
#include <C:\Users\jrhen\Desktop\cryptopp565\dll.h>
#include <C:\Users\jrhen\Desktop\cryptopp565\modes.h>
#include <C:\Users\jrhen\Desktop\cryptopp565\aes.h>
#include <C:\Users\jrhen\Desktop\cryptopp565\filters.h>


void encrypt(char * text, unsigned char key[CryptoPP::AES::DEFAULT_KEYLENGTH], unsigned char iv[CryptoPP::AES::BLOCKSIZE]);

void decrypt(std::string ciphertext, unsigned char key[CryptoPP::AES::DEFAULT_KEYLENGTH], unsigned char iv[CryptoPP::AES::BLOCKSIZE]);
