#include <bits/stdc++.h>
using namespace std;

char sub[26];

int main() {

	for (int i = 0; i < 26; i ++)
		sub[i] = 'A' + i;

	sub[(int)('o' - 'a')] = 't';
	sub[(int)('z' - 'a')] = 'h';
	sub[(int)('n' - 'a')] = 'e';
	
	sub[(int)('c' - 'a')] = 's';
	
	sub[(int)('f' - 'a')] = 'n';
	sub[(int)('l' - 'a')] = 'o';
	
	sub[(int)('q' - 'a')] = 'a';
	sub[(int)('h' - 'a')] = 'p';
	sub[(int)('b' - 'a')] = 'd';
	
	sub[(int)('s' - 'a')] = 'i';
	sub[(int)('j' - 'a')] = 'r';
	sub[(int)('x' - 'a')] = 'c';
	
	sub[(int)('w' - 'a')] = 'w';
	sub[(int)('y' - 'a')] = 'g';
	
	sub[(int)('k' - 'a')] = 'f';
	sub[(int)('g' - 'a')] = 'm';
	sub[(int)('r' - 'a')] = 'l';
	
	sub[(int)('a' - 'a')] = 'x';
	sub[(int)('v' - 'a')] = 'y';
	
	sub[(int)('d' - 'a')] = 'v';
	sub[(int)('p' - 'a')] = 'b';
	sub[(int)('m' - 'a')] = 'k';
	sub[(int)('e' - 'a')] = 'u';

	string str;
	while (cin >> str) {
		for (int i = 0; i < str.size(); i ++)
			if ('a' <= str[i] && str[i] <= 'z')
				cout << sub[(int)(str[i] - 'a')];
		cout << ' ';
	}
}
