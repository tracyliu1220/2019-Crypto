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

int main() {
    std::string  plain   = "Hello World!";
    CryptoPP::byte  key[16] = {'1', '2', '3', '4', '5', '6', '7', '8',
                               '9', '0', '1', '2', '3', '4', '5', '6'};
    std::string  cipher, encoded, recovered;

    CryptoPP::ECB_Mode<AES>::Encryption 

    encoded.clear();
    CryptoPP::StringSource(cipher, true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(encoded)
        )
    );
    std::cout << encoded << std::endl;
}

