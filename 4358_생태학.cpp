#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include<sstream>
#include<cmath>
using namespace std;
/*
4358_ปýลยวะ
*/
bool cmp(pair<string, double> a, pair<string, double> b) {
	return a.first < b.first;
}
int main() {
	map<string, double> m;
	string str;
	double cnt = 0;
	while (getline(cin, str)) {
		cnt += 1;
		if (m.count(str) > 0) {
			m[str] += 1;
		}
		else {
			m.insert({ str,1 });
		}
	}
	vector<pair<string, double>> v;
	for (auto iter : m) {
		v.push_back({ iter.first, iter.second / cnt });
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << " ";
		double cal = v[i].second * 100;
		printf("%.4f\n", round(cal * 10000) / 10000);
	}
	return 0;
}