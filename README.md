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

## References:
Here are some resources I used while writing the SHA code, they provide a good (very technical and official) explanation of SHA 

NIST standard for SHA256: http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
                          http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
RFC standard for SHA256:  https://tools.ietf.org/html/rfc4634
Test inputs + outputs:    https://www.di-mgt.com.au/sha_testvectors.html


