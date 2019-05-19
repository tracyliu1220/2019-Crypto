#include <iostream>
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/rsa.h"
#include "cryptopp/integer.h"
using namespace CryptoPP;
using namespace std;

int main() {
    SHA256 hash;
    string message = "Bitcoin is a cryptocurrency,a form of electronic cash.";
    string digest;
    
    StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    cout << digest << endl;        
}
