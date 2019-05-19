#include <iostream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/rsa.h"
#include "cryptopp/integer.h"
using namespace CryptoPP;
using namespace std;

/* part 2-1
int main() {
    SHA256 hash;
    string message = "Bitcoin is a cryptocurrency,a form of electronic cash.";
    string digest;
    
    StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    cout << digest << endl;        
}
*/

int main() {
    SHA256 hash;
    string initial = "00000002478BF60C4498D445C69E3CFF13B57A42644381919E0D63855B86CF08"; // 7
    string preview = initial;
    string encoded;
    string message;
    string digest;
    int endup = 0;
    srand((long long)time(NULL));
    
    for (int leading_zeroes = 8; leading_zeroes <= 64; leading_zeroes ++) {
        while (1) {
            // nonce
            long long cur_nonce = rand() % (1LL << 28) + (1LL << 28) * 4;
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

        }
        // change for next round
        preview = digest;
    }
}
