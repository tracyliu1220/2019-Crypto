#include <iostream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/rsa.h"
#include "cryptopp/integer.h"
using namespace CryptoPP;
using namespace std;

int main() {
    SHA256 hash;
    string initial = "000000B1010437E82D8E7D6550D87497E0503A53358B012EDA32C000D47B348B"; // 7
    string preview = initial;
    string encoded;
    string message;
    string digest;
    int endup = 0;
    
    for (int leading_zeroes = 7; leading_zeroes <= 64; leading_zeroes ++) {
        for (int nonce_cnt = 0; nonce_cnt < (1LL << 32); nonce_cnt ++) {
            // nonce
            int cur_nonce = nonce_cnt;
            char ch;
            string nonce;
            for (int i = 0; i < 8; i ++) {
                int cur = cur_nonce & 15; // 1111
                cur_nonce >>= 4;
                if (cur < 10) ch = '0' + cur;
                else ch = 'A' + cur - 10;
                nonce = ch + nonce;
            }

            // encoded hex string
            encoded = preview + nonce;

            // hex decoder
            HexDecoder decoder;
            decoder.Put( (byte*)encoded.data(), encoded.size() );
            decoder.MessageEnd();
            word64 size = decoder.MaxRetrievable();
            message.resize(size);
            decoder.Get( (byte*)&message[0], message.size() );

            // sha256
            digest.clear();
            StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
            
            // verify
            int legal = 1;
            for (int i = 0; i < leading_zeroes; i ++)
                if (digest[i] != '0') legal = 0;
            if (digest[leading_zeroes] == '0') legal = 0;
            
            // if success
            if (legal) {
                cout << leading_zeroes << endl;
                cout << "preview: " << preview << endl;;
                cout << "nonce:   " << nonce << endl;
                cout << "hash:    " << digest << endl;
                cout << "------" << endl;
                break;
            }

            // if no
            if (nonce_cnt == (1LL << 32) - 1) {
                endup = 1;
                cout << "end" << endl;
                break;
            }
        }
        // change for next round
        preview = digest;
        if (endup) break;
    }
}
