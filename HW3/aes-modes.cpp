#include <iostream>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"

// enc/ECB
std::string Encrypt(std::string input, 
                    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E,
                    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    std::string result;
    CryptoPP::StringSource(input, true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::StringSink(result),
            paddingMethod
        )
    );
    return result;
}

// enc/CBC
std::string Encrypt(std::string input, 
                    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption E,
                    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    std::string result;
    CryptoPP::StringSource(input, true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::StringSink(result),
            paddingMethod
        )
    );
    return result;
}

// dec/ECB
std::string Decrypt(std::string input, 
                    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption D,
                    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    std::string result;
    CryptoPP::StringSource(input, true,
        new CryptoPP::StreamTransformationFilter(D,
            new CryptoPP::StringSink(result),
            paddingMethod
        )
    );
    return result;
}

// dec/CBC
std::string Decrypt(std::string input, 
                    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption D,
                    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    std::string result;
    CryptoPP::StringSource(input, true,
        new CryptoPP::StreamTransformationFilter(D,
            new CryptoPP::StringSink(result),
            paddingMethod
        )
    );
    return result;
}

int main() {

    // Parameters
    std::string state   = "dec"; // enc, dec
    std::string mode    = "ECB"; // ECB, CBC
    std::string padding = "zeros"; // zeros, pkcs
    // std::string input   = "Hello World!";
    // std::string input   = "2E9868AA6EAE72184B4A8881F3DFB26B";
    std::string input   = "3AB2D9A5B00C722C5799A1C6BF5287B80468BF5F55A1A6C7576CB7E62CC924234369CA8F412F1345C87C4D7C1339C684";
    std::string _key    = "1234567890123456";
    std::string _iv     = "0000000000000000";
    
    // Other Variables
    std::string result, encoded;
    int key_length = CryptoPP::AES::BLOCKSIZE;
    CryptoPP::byte key[key_length] = {'1', '2', '3', '4', '5', '6', '7', '8', 
                                      '9', '0', '1', '2', '3', '4', '5', '6'};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]  = {'0', '0', '0', '0', '0', '0', '0', '0', 
                                                    '0', '0', '0', '0', '0', '0', '0', '0'};

    // Set Input Type
    if (state == "dec") {
        CryptoPP::HexDecoder decoder;
        decoder.Put((CryptoPP::byte*)input.data(), input.size());
        std::string decoded;
        decoded.resize(decoder.MaxRetrievable());
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
        input = decoded;
    }

    // Set Key and IV
    for (int i = 0; i < key_length; i ++) key[i] = _key[i];
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i ++) iv[i] = _iv[i];    

    // Set Padding
    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod;
    if (padding == "zeros") 
        paddingMethod = CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING;
    if (padding == "pkcs")  
        paddingMethod = CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING;
    
    // Set Mode and Encrypt
    if (state == "enc" && mode == "ECB") {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption ECB;
        ECB.SetKey(key, key_length);
        result = Encrypt(input, ECB, paddingMethod);
    }
    if (state == "enc" && mode == "CBC") {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption CBC;
        CBC.SetKeyWithIV(key, key_length, iv);
        result = Encrypt(input, CBC, paddingMethod);
    }

    // Set Mode and Decrypt
    if (state == "dec" && mode == "ECB") {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption ECB;
        ECB.SetKey(key, key_length);
        result = Decrypt(input, ECB, paddingMethod);
    }
    if (state == "dec" && mode == "CBC") {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption CBC;
        CBC.SetKeyWithIV(key, key_length, iv);
        result = Decrypt(input, CBC, paddingMethod);
    }

    // Output
    if (state == "dec")
        std::cout << result << std::endl;
    if (state == "enc") {
        encoded.clear();
        CryptoPP::StringSource(result, true,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(encoded)
            )
        );
        std::cout << encoded << std::endl;
    }
}
