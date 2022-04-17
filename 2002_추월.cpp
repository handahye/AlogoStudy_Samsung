#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>
#include<sstream>

using namespace std;
/*
2002 Ãß¿ù
*/

int main() {
	int N;
	cin >> N;
	unordered_map<string, int> m;
	int ans = 0;
	vector<int> v(N);
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		m.insert({ str, i });
	}
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		v[i] = m[str];
	}
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (v[i] > v[j]) {
				ans++;
				break;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}