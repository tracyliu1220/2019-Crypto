#include <bits/stdc++.h>
using namespace std;

int main() {
    int e = 472;
    int c = 0;
    int f = 1;
    int a = 6;
    int mod = 3415;
    for (int i = 8; i >= 0; i --) {
        int state = (1 << i) & e;
        if (state) cout << 1 << ' ';
        else cout << 0 << ' ';
        f = f * f % mod;
        c *= 2;
        if (state) {
            f = f * a % mod;
            c += 1;
        }
        cout << c << ' ' << f << '\n';
    }
}
