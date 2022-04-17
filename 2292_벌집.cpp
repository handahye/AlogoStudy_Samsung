#include <iostream>
#include <vector>
#include<algorithm>
#include<string>
#include<cstring>
/*
#2292_¹úÁý
*/
using namespace std;

int main() {
	int N;
	cin >> N;

	int i = 2, j = 5, cnt = 2;
	while (1) {
		if (N == 1) {
			cout << 1 << "\n";
			return 0;
		}
		if (i <= N && i + j >= N) {
			cout << cnt;
			return 0;
		}
		i = i + j + 1;
		j += 6;
		cnt++;
	}

	return 0;
}