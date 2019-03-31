# HW3

## Download Crypto++

Download and unzip
```
wget https://www.cryptopp.com/cryptopp810.zip
unzip -aoq cryptopp810.zip -d cryptopp
```

Install
```
cd cryptopp
make
```

## Include
```
#include "cryptopp/modes.h"
```

## Compiling

```
g++ -DNDEBUG -g2 -O2 $CPPFILE ./cryptopp/libcryptopp.a
```

## Reference

- [AES](https://www.cryptopp.com/wiki/Advanced_Encryption_Standard)
- [ECB Mode](https://www.cryptopp.com/wiki/ECB_Mode)
- [ArraySource](https://www.cryptopp.com/wiki/ArraySource)
- [AES MixColumns](http://www.angelfire.com/biz7/atleast/mix_columns.pdf)
