#include <iostream>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"

// enc/ECB
void Encrypt(std::vector<CryptoPP::byte> & input, 
             std::vector<CryptoPP::byte> & result, 
             CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption E,
             CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    
    int n = input.size() / CryptoPP::AES::BLOCKSIZE;
    if (input.size() % CryptoPP::AES::BLOCKSIZE) n ++;
    n *= CryptoPP::AES::BLOCKSIZE;

    result.resize(n);
    CryptoPP::ArraySink cs(&result[0], result.size());
    
    CryptoPP::ArraySource(input.data(), input.size(), true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::Redirector(cs),
            paddingMethod
        )
    );
}

// enc/CBC
void Encrypt(std::vector<CryptoPP::byte> & input, 
             std::vector<CryptoPP::byte> & result, 
             CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption E,
             CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    
    int n = input.size() / CryptoPP::AES::BLOCKSIZE;
    if (input.size() % CryptoPP::AES::BLOCKSIZE) n ++;
    n *= CryptoPP::AES::BLOCKSIZE;

    result.resize(n);
    CryptoPP::ArraySink cs(&result[0], result.size());
    
    CryptoPP::ArraySource(input.data(), input.size(), true,
        new CryptoPP::StreamTransformationFilter(E,
            new CryptoPP::Redirector(cs),
            paddingMethod
        )
    );
}

// dec/ECB
void Decrypt(std::vector<CryptoPP::byte> & input, 
             std::vector<CryptoPP::byte> & result, 
             CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption D,
             CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    
    result.resize(input.size());
    CryptoPP::ArraySink cs(&result[0], result.size());
    
    CryptoPP::ArraySource(input.data(), input.size(), true,
        new CryptoPP::StreamTransformationFilter(D,
            new CryptoPP::Redirector(cs),
            paddingMethod
        )
    );
	result.resize(cs.TotalPutLength());
}

// dec/CBC
void Decrypt(std::vector<CryptoPP::byte> & input, 
             std::vector<CryptoPP::byte> & result, 
             CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption D,
             CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingMethod) {
    
    result.resize(input.size());
    CryptoPP::ArraySink cs(&result[0], result.size());
    
    CryptoPP::ArraySource(input.data(), input.size(), true,
        new CryptoPP::StreamTransformationFilter(D,
            new CryptoPP::Redirector(cs),
            paddingMethod
        )
    );
	result.resize(cs.TotalPutLength());
}

void Print(std::vector<CryptoPP::byte> & result) {
    for (int i = 0; i < result.size(); i ++)
        // if ((int)result[i] > 16) 
            std::cout << result[i];
    std::cout << std::endl;
}

/*
Hello World!
2E9868AA6EAE72184B4A8881F3DFB26B
A1F32C84BE355E41BA350FAFE9B6B001
DDC194E6D0F185AE03A04DD4150435B4
817BC015A16257FF845BFA0C4DC2FCBB
*/

/*
AES is efficient in both software and hardware.
3AB2D9A5B00C722C5799A1C6BF5287B80468BF5F55A1A6C7576CB7E62CC924234369CA8F412F1345C87C4D7C1339C684
3AB2D9A5B00C722C5799A1C6BF5287B80468BF5F55A1A6C7576CB7E62CC92423699C3207946E9B88844D81939A5C0982
C9A03BCE0555B5FB2EC1D30A154FAE7C0AD045EA3C5738C788CED8007A5F1243143FF487BC3F8E512B2EF3AE96AE4A13
C9A03BCE0555B5FB2EC1D30A154FAE7C0AD045EA3C5738C788CED8007A5F124387A9144E595E3CEBD1382AF0DCC536B2
*/

int main() {

    // Parameters
    std::string state   = "dec"; // enc, dec
    std::string mode    = "CBC"; // ECB, CBC
    std::string padding = "pkcs"; // zeros, pkcs
    std::string _input  = "C9A03BCE0555B5FB2EC1D30A154FAE7C0AD045EA3C5738C788CED8007A5F124387A9144E595E3CEBD1382AF0DCC536B2";
    std::string _key    = "1234567890123456";
    std::string _iv     = "0000000000000000";
    
    // Other Variables
    std::string encoded;
    int key_length = CryptoPP::AES::BLOCKSIZE;
    CryptoPP::byte key[key_length] = {'1', '2', '3', '4', '5', '6', '7', '8', 
                                      '9', '0', '1', '2', '3', '4', '5', '6'};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]  = {'0', '0', '0', '0', '0', '0', '0', '0', 
                                                    '0', '0', '0', '0', '0', '0', '0', '0'};
    std::vector<CryptoPP::byte> input, result;
    input.resize(_input.size());

    // Set Input Type
    if (state == "dec") {
        CryptoPP::HexDecoder decoder;
        decoder.Put((CryptoPP::byte*)_input.data(), _input.size());
        std::string decoded;
        decoded.resize(decoder.MaxRetrievable());
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
        _input = decoded;
        input.resize(_input.size());
    }

    // Set Key and IV
    for (int i = 0; i < key_length; i ++) key[i] = _key[i];
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i ++) iv[i] = _iv[i];    
    for (int i = 0; i < _input.size(); i ++) input[i] = _input[i];    

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
        Encrypt(input, result, ECB, paddingMethod);
    }
    if (state == "enc" && mode == "CBC") {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption CBC;
        CBC.SetKeyWithIV(key, key_length, iv);
        Encrypt(input, result, CBC, paddingMethod);
    }

    // Set Mode and Decrypt
    if (state == "dec" && mode == "ECB") {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption ECB;
        ECB.SetKey(key, key_length);
        Decrypt(input, result, ECB, paddingMethod);
    }
    if (state == "dec" && mode == "CBC") {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption CBC;
        CBC.SetKeyWithIV(key, key_length, iv);
        Decrypt(input, result, CBC, paddingMethod);
    }

    if (state == "dec")
        Print(result);
    if (state == "enc") {
        CryptoPP::HexEncoder encoder;
        std::vector<CryptoPP::byte> encoded;
        encoder.Put(result.data(), result.size());
        encoded.resize(encoder.MaxRetrievable());
        encoder.Get(encoded.data(), encoded.size());
        Print(encoded);
    }
}
