# BMPCrypter
A project I made to teach myself a bit of C and practise using encryption. Uses a BMP image (hashed using my own implemented SHA256) as an encryption key for AES


Can't say I put this together very professionally

library was added in really badly, basically just dumped the files in a folder on my desktop and linked them.


## How it works

Load bmp image file -> hash pixel colour data -> use as key for AES


## Files:

-Main.cpp is where the program runs from

-AES.cpp interfaces with the crypto library to perform encryption or decryption

-SHA.cpp is my own implemetation of SHA-256 based off NIST documentation

-FileHandling.cpp reads in BMP files and extracts pixel data