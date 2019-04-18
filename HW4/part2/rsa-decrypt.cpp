#include <iostream>
#include <sstream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/rsa.h"
#include "cryptopp/integer.h"

int c_to_i(char c) {
    if ('a' <= c && c <= 'z') 
        return (int)(c - 'a') + 10;
    if ('A' <= c && c <= 'Z')
        return (int)(c - 'A') + 10;
    else
        return (int)(c - '0');
}

int main() {

    // set keys
    CryptoPP::Integer n("0xa0c432951d9e7da10fa929ba570bfee52db56fc477e60b742581a35d1723ad6f");
    CryptoPP::Integer d("0x974f3eaa763ad0979644dbfaac47867bd87b4c5c8b7fcd72943d0dde4303639");
    CryptoPP::RSA::PublicKey pubKey;
    pubKey.Initialize(n, d);

    // Enc
    std::string input = "404ea0a1c26fc6562ff17a61849520e0fdf70654c6460b0954918e8447d6cdba";
    std::string cipher;
    for (int i = 0; i < input.size(); i += 2) {
        int tmp = c_to_i(input[i]) * 16;
        tmp += c_to_i(input[i + 1]);
        cipher = cipher + (char)tmp;
    }
    CryptoPP::Integer c((const CryptoPP::byte *)cipher.data(), cipher.size());
    CryptoPP::Integer m = pubKey.ApplyFunction(c);

    // convert to string
    std::string result, str;
    std::stringstream ss;
    ss << std::hex << m;
    ss >> str;

    for (int i = 0; i < str.size() - 1; i += 2) {
        int tmp = 0;
        tmp += c_to_i(str[i]) * 16;
        tmp += c_to_i(str[i + 1]);
        result = result + (char)tmp;
    }
    std::cout << result << std::endl;
}
