#include <bits/stdc++.h>
using namespace std;

void print(int x) {
    bitset<8> b(x);
    cout << b << '\n';
}

int mul(int a, int b) {
    int out = 0;
        while (a) {
            if (a % 2) out ^= b;
            b <<= 1;
            a >>= 1;
            
            int state = 0;
            if (b >= (1<<8)) state = 1;
            b &= (1<<8) - 1;
            if (state) b ^= 0x1B;
        }
    return out;
}

int main() {
    int s[4][4] = {{0xd7, 0x01, 0x6b, 0x7c},
                   {0x30, 0xf2, 0x63, 0xfe},
                   {0xc5, 0x7b, 0x76, 0x2b},
                   {0x77, 0xab, 0x67, 0x6f}};
    int c[4][4] = {{0x02, 0x03, 0x01, 0x01},
                   {0x01, 0x02, 0x03, 0x01},
                   {0x01, 0x01, 0x02, 0x03},
                   {0x03, 0x01, 0x01, 0x02}};
    int r[4][4] = {0};
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            for (int k = 0; k < 4; k ++) {
                r[j][i] ^= mul(c[j][k], s[k][i]);
            }
        }
    }

    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++)
            cout << hex << r[i][j] << ' ';
        cout << '\n';
    }
}
