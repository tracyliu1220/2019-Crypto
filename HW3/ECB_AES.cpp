/*
AES is efficient in both software and hardware.
41455320697320656666696369656E7420696E20626F746820736F66747761726520616E642068617264776172652E
1234567890123456
31323334353637383930313233343536
*/

#include <iostream>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"


std::string Padding(std::string input, int key_length, bool state) { // 0: zeros, 1: PKCS7
    if (input.size() % key_length == 0) return input;
    int n = (input.size() / key_length + 1) * key_length;
    
    char add;
    if (state) add = (char)(n - input.size());
    else add = (char)0;
    
    std::string plain(input);
    for (int i = input.size(); i < n; i ++)
        plain = plain + add;

    return plain;
} 

void PrintEncoded(std::string encoded) {
    for (int i = 0; i < encoded.size() - 32; i ++)
        std::cout << encoded[i];
    std::cout << std::endl;
}

// Encryption
std::string Encrypt(std::string plain, CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E) {
    std::string cipher;
    CryptoPP::StringSource(plain, true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::StringSink(cipher)
        )
    );
    return cipher;
}

int main() {

    bool state = true;
    int  key_length = 16;
    std::string    input   = "Hello World!";
    std::string    plain   = Padding(input, key_length, state);
    // CryptoPP::byte plain[16] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 
    //                            'r', 'l', 'd', '!', 0x00, 0x00, 0x00, 0x00};
    CryptoPP::byte key[key_length] = {'1', '2', '3', '4', '5', '6', '7', '8', 
                                      '9', '0', '1', '2', '3', '4', '5', '6'};
    std::string  cipher, encoded, recovered;

    // plain = Padding(plain, 16, true);
    //for (int i = 12; i < 16; i ++) {
    //    plain[i] = 0x00;
    //}

    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E;
    E.SetKey(key, 16);
    cipher = Encrypt(plain, E);

    encoded.clear();
    CryptoPP::StringSource(cipher, true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(encoded)
        )
    );
    PrintEncoded(encoded);
}
