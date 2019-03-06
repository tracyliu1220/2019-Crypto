#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 0; i < 8; i ++) {
        cout << "0b";
        for (int j = 0; j < i; j ++) {
            cout << "000000";
        }
        cout << "111111";
        for (int j = i + 1; j < 8; j ++) {
            cout << "000000";
        }
        cout << '\n';
    }
}
