#include <bits/stdc++.h>
using namespace std;

int enc[13] = {3, 11, 5, 7, 17, 21, 0, 11, 14, 8, 7, 13, 9};

int main() {
	string str = "sendmoremoney";
	for (int i = 0; i < 13; i ++) {
		cout << (char)('a' + (str[i] - 'a' + enc[i]) % 26);
	}
}
