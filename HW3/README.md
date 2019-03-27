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

## Compiling

```
g++ -DNDEBUG -g2 -O2 $CPPFILE ./cryptopp/libcryptopp.a
```

## Reference

- [AES](https://www.cryptopp.com/wiki/Advanced_Encryption_Standard)
- [ECB Mode](https://www.cryptopp.com/wiki/ECB_Mode)


