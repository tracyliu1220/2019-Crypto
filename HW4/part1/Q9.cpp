#include <bits/stdc++.h>
using namespace std;

const int Q = 23;
const int A = 1;

int division(int a, int b) {
    for (int i = 0; i < Q; i ++) {
        if (b * i % Q == a)
            return i;
    }
}

pair<int, int> add(int px, int py, int qx, int qy) {
    int l, l1, l2;
    if (px == qx && py == qy) {
        l1 = 3 * px * px + A;
        l2 = 2 * py;
    } else {
        l1 = qy - py;
        l2 = qx - px;
    }
    while (l1 < 0) l1 += Q;
    while (l2 < 0) l2 += Q;    
    l = division(l1 % Q, l2 % Q);
    int xr = l * l - px - qx;
    while (xr < 0) xr += Q; xr %= Q;
    int yr = l * (px - xr) - py;
    while (yr < 0) yr += Q; yr %= Q;
    return {xr, yr};
}

int main() {
    int op;
    while (cin >> op) {
        pair<int, int> ans;
        if (op == 1) {
            int a, x, y;
            cin >> a >> x >> y;
            int curx = x, cury = y;
            a --;
            while (a --) {
                ans = add(curx, cury, x, y);
                curx = ans.first;
                cury = ans.second;
            }
        } else {
            int px, py, qx, qy;
            cin >> px >> py >> qx >> qy;
            ans = add(px, py, qx, qy);
        }
        cout << ans.first << ' ' << ans.second << '\n';
    }
}
