#include <bits/stdc++.h>
using namespace std;

void print(int x) {
    bitset<8> b(x);
    cout << b << '\n';
}

int main() {
    int a, b;
    while (cin >> hex >> a >> b) {
        int out = 0;
        while (a) {
            if (a % 2) out ^= b;
            b <<= 1;
            a >>= 1;
        }
        cout << hex << out << '\n';
        print(out);
    }
}
