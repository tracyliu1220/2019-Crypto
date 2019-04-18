# HW4 part2
Raw RSA Encrypt and Decrypt with custom key

## Encrypt

### set keys
```cpp
CryptoPP::Integer n("0xaf195de7988cfaa1dbb18c5862e3853f0e79a12bbfa7aa326a52da97caa60c39");
CryptoPP::Integer e("0x11");
CryptoPP::RSA::PublicKey pubKey;
pubKey.Initialize(n, e);
```

### encrypt function
```cpp
CryptoPP::Integer m((const CryptoPP::byte *)plain.data(), plain.size());
CryptoPP::Integer c = pubKey.ApplyFunction(m);
```

### output
```cpp
std::cout << std::hex << c << std::endl;
```

## Decrypt
use the same function as encrypt because of the lack of `e`

### set keys
```cpp
CryptoPP::Integer n("0xa0c432951d9e7da10fa929ba570bfee52db56fc477e60b742581a35d1723ad6f");
CryptoPP::Integer d("0x974f3eaa763ad0979644dbfaac47867bd87b4c5c8b7fcd72943d0dde4303639");
CryptoPP::RSA::PublicKey pubKey;
pubKey.Initialize(n, d);
```

### input: from hex to ascii
```cpp
std::string input = "404ea0a1c26fc6562ff17a61849520e0fdf70654c6460b0954918e8447d6cdba";
std::string cipher;
for (int i = 0; i < input.size(); i += 2) {
    int tmp = c_to_i(input[i]) * 16;
    tmp += c_to_i(input[i + 1]);
    cipher = cipher + (char)tmp;
}
```

### decrypt function
```cpp
CryptoPP::Integer c((const CryptoPP::byte *)cipher.data(), cipher.size());
CryptoPP::Integer m = pubKey.ApplyFunction(c);
```

### output: from CryptoPP::Integer to string
using stringstream

```cpp
#include <sstream>
```
```cpp
std::string result, str;
std::stringstream ss;
ss << std::hex << m;
ss >> str;
```

### output: from hex to ascii
```cpp
for (int i = 0; i < str.size() - 1; i += 2) {
    int tmp = 0;
    tmp += c_to_i(str[i]) * 16;
    tmp += c_to_i(str[i + 1]);
    result = result + (char)tmp;
}
```

### output
```
std::cout << result << std::endl;
```

## Reference

- [Raw RSA](https://www.cryptopp.com/wiki/Raw_RSA)
- [stringstream](https://dotblogs.com.tw/v6610688/2013/11/08/cplusplus_stringstream_int_and_string_convert_and_clear)
