#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    int n;
    while (1) {
        cin >> n;
        cin >> hex >> a;
        n --;
        while (n --) {
            cin >> hex >> b;
            a ^= b;
        }
        cout << hex << a << '\n';
    }
}
