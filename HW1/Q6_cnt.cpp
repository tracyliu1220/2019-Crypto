#include <bits/stdc++.h>
using namespace std;

int cnt[26] = {0};

int main() {
	string str;
	while (cin >> str) {
		for (int i = 0; i < str.size(); i ++) {
			if ('a' <= str[i] && str[i] <= 'z')
				cnt[(int)(str[i] - 'a')] ++;
		}
	}

	for (int i = 0; i < 26; i ++) {
		cout << "  " <<  (char)('a' + i) << ' ' << cnt[i] << '\n';
	}
}
