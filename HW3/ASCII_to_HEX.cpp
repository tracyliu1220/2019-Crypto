#include <bits/stdc++.h>
using namespace std;

int main() {
    
    string str;
    while (getline(cin, str)) {
        for (int i = 0; i < str.size(); i ++) {
            printf("%02X", (int)str[i]);
        }
        printf("\n");
    }
}
