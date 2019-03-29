#include <iostream>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"

void Padding(std::string input, 
             std::vector<CryptoPP::byte> & plain, 
             int length, bool state) { // 0: zeros, 1: PKCS#7
    
    if ((input.size() + 1) % length == 0) {
        plain.resize(input.size() + 1);
        for (int i = 0; i < input.size(); i ++)
            plain[i] = input[i];
        plain[input.size()] = (char)0;
        return;
    }

    int n = ((input.size() + 1) / length + 1) * length;
    
    char add;
    if (state) add = (char)(n - (input.size() + 1));
    else add = (char)0;
    
    plain.resize(n);
    for (int i = 0; i < input.size(); i ++)
        plain[i] = input[i];
    plain[input.size()] = (char)0;
    for (int i = input.size() + 1; i < n; i ++)
        plain[i] = add;
} 

// ECB Mode
void Encrypt(std::vector<CryptoPP::byte> & plain, 
             std::vector<CryptoPP::byte> & cipher, 
             CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E) {
    
    cipher.resize(plain.size());
    CryptoPP::ArraySink cs(&cipher[0], cipher.size());
    
    CryptoPP::ArraySource(plain.data(), plain.size(), true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::Redirector(cs)
        )
    );
}

// CBC Mode
void Encrypt(std::vector<CryptoPP::byte> & plain, 
             std::vector<CryptoPP::byte> & cipher, 
             CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption E) {
    
    cipher.resize(plain.size());
    CryptoPP::ArraySink cs(&cipher[0], cipher.size());
    
    CryptoPP::ArraySource(plain.data(), plain.size(), true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::Redirector(cs)
        )
    );
}

int main() {

    // parameters
    bool padding_state = true;  // 0: zeros, 1: PKCS#7
    int  key_length = 16;
    std::string input = "AES is efficient in both software and hardware.";
    std::string mode  = "CBC";

    std::vector<CryptoPP::byte> plain, cipher;

    Padding(input, plain, CryptoPP::AES::BLOCKSIZE, padding_state);
    
    CryptoPP::byte key[key_length] = {'1', '2', '3', '4', '5', '6', '7', '8', 
                                      '9', '0', '1', '2', '3', '4', '5', '6'};
    CryptoPP::byte iv[key_length]  = {'0', '0', '0', '0', '0', '0', '0', '0', 
                                      '0', '0', '0', '0', '0', '0', '0', '0'};

    // EBC
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption ECB;
    ECB.SetKey(key, key_length);

    // CBC
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption CBC;
    CBC.SetKeyWithIV(key, key_length, iv);
    
    if (mode == "ECB") Encrypt(plain, cipher, ECB);
    if (mode == "CBC") Encrypt(plain, cipher, CBC);

    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    encoder.Put(cipher.data(), cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
}
