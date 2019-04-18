#include <iostream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/rsa.h"
#include "cryptopp/integer.h"

int main() {

    // set keys
    CryptoPP::Integer n("0xaf195de7988cfaa1dbb18c5862e3853f0e79a12bbfa7aa326a52da97caa60c39");
    CryptoPP::Integer e("0x11");
    CryptoPP::RSA::PublicKey pubKey;
    pubKey.Initialize(n, e);

    // Enc
    std::string plain = "RSA is public key.";

    CryptoPP::Integer m((const CryptoPP::byte *)plain.data(), plain.size());
    CryptoPP::Integer c = pubKey.ApplyFunction(m);
    std::cout << std::hex << c << std::endl;
}
