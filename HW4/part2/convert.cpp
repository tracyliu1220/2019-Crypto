#include <bits/stdc++.h>
using namespace std;

int c_to_i(char c) {
    if ('a' <= c && c <= 'z') 
        return (int)(c - 'a') + 10;
    else
        return (int)(c - '0');
}

int main() {
    string str;
    cin >> str;
    string result;

    cout << (int)'S' << endl;

    for (int i = 0; i < str.size() - 1; i += 2) {
        int tmp = 0;
        tmp += c_to_i(str[i]) * 16;
        tmp += c_to_i(str[i + 1]);
        result = result + (char)tmp;
    }
    cout << result << endl;
}
