#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include<sstream>

using namespace std;
/*
19583 ���̹� ���� ��ȸ
���� ������ȸ�� �Դ��� �� �� ����.
���� ������ȸ �ڸ��� ������ �����־����� �� �� ����.
� ����� ������ȸ ��Ʈ������ �ܼ��� Ʋ����⸸ �ߴ��� �� �� ����.

*/
string s, e, q;
set<string> st;

long long Change(string s) {
	string si = s.substr(0, 2);
	string boon = s.substr(3, 2);

	return 60 * stol(si) + stol(boon);

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> s >> e >> q;
	string str, name;
	int cnt = 0;

	long long S = Change(s);
	long long E = Change(e);
	long long Q = Change(q);


	while (cin.eof() == false) {
		cin >> str;
		string si = str.substr(0, 2);
		string boon = str.substr(3, 2);
		cin >> name;
		long long time = Change(str);
		if (time <= S) {
			st.insert(name);
		}
		else if (E <= time && time <= Q) {
			if (st.count(name) > 0) {
				cnt++;
				st.erase(name);
			}
		}

	}
	cout << cnt;
	return 0;
}