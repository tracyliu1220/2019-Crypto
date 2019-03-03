#include <bits/stdc++.h>
using namespace std;

int main() {
	string cipher = "vpskdjrpawurh";
	string plain = "cashnotneeded";
	for (int i = 0; i < 13; i ++) {
		cout << (cipher[i] - plain[i] + 26) % 26 << ' ';
	}
}
