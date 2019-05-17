#include <bits/stdc++.h>
using namespace std;

map<int, int> themap;

int main() {
    int A = 1;
    int t = 4;
    
    while (t --) {
        A *= 3;
        int x0 = 1;
        int m = 31;
        int cur = x0;
        int cnt = 0;
        themap.clear();
        while(1) {
            if (themap.count(cur)) break;
            cout << cur << ' ';
            themap[cur] = 1;
            cur = cur * A % m;
            cnt ++;
        }
        cout << "\ncount: " << cnt << '\n';
    }
}
