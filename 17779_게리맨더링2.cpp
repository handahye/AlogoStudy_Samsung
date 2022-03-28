#include <iostream>
#include <vector>
#include<algorithm>
/*
#17779 게리맨더링2
1. 구역을 다섯 개의 선거구로 나눠야 하고, 각 구역은 다섯 선거구 중 하나에 포함되어야 한다.
2. 선거구는 구역을 적어도 하나 포함해야 하고, 한 선거구에 포함되어 있는 구역은 모두 연결되어 있어야 한다.
*/
using namespace std;
int A[21][21];
int N;
struct NODE {
	int x, y, d1, d2;
};
vector<NODE> v;
vector<pair<int, int>> d;
void findBoundary(int x, int y, int d1, int d2) {
	int nx = x, ny = y;
	while (1) {
		A[nx][ny] = -1;
		if (nx == x + d1 && ny == y - d1) break;
		nx++;
		ny--;
	}
	nx = x, ny = y;
	while (1) {
		A[nx][ny] = -1;
		if (nx == x + d2 && ny == y + d2) break;
		nx++;
		ny++;
	}
	nx = x + d1, ny = y - d1;
	while (1) {
		A[nx][ny] = -1;
		if (nx == x + d1 + d2 && ny == y - d1 + d2) break;
		nx++;
		ny++;
	}
	nx = x + d2, ny = y + d2;
	while (1) {
		A[nx][ny] = -1;
		if (nx == x + d2 + d1 && ny == y + d2 - d1) break;
		nx++;
		ny--;
	}
}
int solve(int k, int x, int y, int d1, int d2) {
	int total = 0;
	if (k == 1) {
		for (int i = 1; i < x + d1; i++) {
			for (int j = 1; j <= y; j++) {
				if (A[i][j] == -1) {
					break;
				}
				total += A[i][j];
			}
		}
	}
	else if (k == 2) {
		for (int i = 1; i <= x + d2; i++) {
			for (int j = N; j > y; j--) {
				if (A[i][j] == -1) {
					break;
				}
				total += A[i][j];
			}
		}
	}
	else if (k == 3) {
		for (int i = x + d1; i <= N; i++) {
			for (int j = 1; j < y - d1 + d2; j++) {
				if (A[i][j] == -1) {
					break;
				}
				total += A[i][j];
			}
		}
	}
	else if (k == 4) {
		for (int i = x + d2 + 1; i <= N; i++) {
			for (int j = N; j >= y - d1 + d2; j--) {
				if (A[i][j] == -1) {
					break;
				}
				total += A[i][j];
			}
		}
	}
	return total;
}
void copyMap(int a[][21], int b[][21]) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			a[i][j] = b[i][j];
		}
	}
}
int main() {
	int sum = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			sum += A[i][j];
		}
	}
	//경계 길이 조합 
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			d.push_back({ i,j });
		}
	}
	//기준점 조합
	for (int i = 0; i < d.size(); i++) {
		int d1 = d[i].first;
		int d2 = d[i].second;
		for (int x = 1; x <= N; x++) {
			if (x + d1 + d2 > N) continue;
			for (int y = 1; y <= N; y++) {
				if (y - d1 < 1 || y + d2 > N) continue;
				v.push_back({ x,y,d1,d2 });
			}
		}
	}
	int minN = 987654321;
	for (int i = 0; i < v.size(); i++) {
		int x = v[i].x;
		int y = v[i].y;
		int d1 = v[i].d1;
		int d2 = v[i].d2;
		vector<pair<int, int>> person;
		int tmp[21][21];
		copyMap(tmp, A);
		findBoundary(x, y, d1, d2);
		int five = sum;
		for (int k = 1; k <= 4; k++) {
			int total = solve(k, x, y, d1, d2);
			five -= total;
			person.push_back({ total, k });
		}
		person.push_back({ five, 5 });
		sort(person.begin(), person.end());
		minN = min(minN, person[4].first - person[0].first);
		copyMap(A, tmp);
	}
	cout << minN << "\n";
	return 0;
}