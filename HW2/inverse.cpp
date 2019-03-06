#include <bits/stdc++.h>
using namespace std;

map<int, int> m;

int main() {

    int actual = 64;
    int total = 64;
    int mod = 8;

    int out[500];
    for (int i = 0; i < 500; i ++) out[i] = -1;

    int n;
    for (int i = 0; i < total; i ++) {
        cin >> n;
        n --;
        m[n] = i;
    }

    map<int, int>::iterator iter;
    int cnt = 0;
    for (iter = m.begin(); iter != m.end(); iter ++) {
        out[iter->first] = iter->second;
    }

    for (int i = 0; i < actual; i ++) {
        if (out[i] < 10 && out[i] != -1) cout << ' ';
        cout << out[i] << ", ";
        if ((i + 1) % mod == 0) cout << '\n';
    }

}
