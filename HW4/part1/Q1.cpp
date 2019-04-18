#include <bits/stdc++.h>
using namespace std;

map<int, int> themap;

int main() {
    int x0 = 1;
    int m = 31;
    int A = 3 * 3 * 3 * 3;
    int cur = x0;
    int cnt = 0;
    
    while(1) {
        if (themap.count(cur)) break;
        cout << cur << ' ';
        themap[cur] = 1;
        cur = cur * A % m;
        cnt ++;
    }
    cout << "\ncount: " << cnt << '\n';
}
