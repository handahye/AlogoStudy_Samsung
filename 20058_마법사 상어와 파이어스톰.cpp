#include <iostream>
#include <vector>
#include<algorithm>
#include<functional>
#include<queue>
#include<cmath>
/*
#20058_마법사 상어와 파이어스톰
*/
using namespace std;
int n, N, Q, A[101][101];
int ans = 0;
int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,-1,1 };
int visit[101][101] = { 0, };
void rotation(int size) {
	int L = pow(2, size);
	int r = 0, c = 0;
	while (1) {
		if (r >= N)break;
		queue<int> q;
		for (int i = r; i < r + L; i++) {
			for (int j = c; j < c + L; j++) {
				q.push(A[i][j]);
				A[i][j] = 0;
			}
		}
		for (int i = c + L - 1; i >= c; i--) {
			for (int j = r; j < r + L; j++) {
				int ice = q.front();
				q.pop();
				A[j][i] = ice;
			}
		}
		c = c + L;
		if (c >= N) {
			c = 0;
			r = r + L;
		}
	}
}
void fireStorm() {
	int cnt[101][101] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int d = 0; d < 4; d++) {
				int nr = i + dr[d];
				int nc = j + dc[d];
				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
				if (A[nr][nc] > 0) cnt[i][j]++;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (cnt[i][j] < 3) A[i][j]--;
		}
	}
}
int remainIce() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] <= 0) continue;
			sum += A[i][j];
		}
	}
	return sum;
}
void chkMass(int r, int c, int cnt) {
	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
		if (A[nr][nc] > 0 && visit[nr][nc] == 0) {
			visit[nr][nc] = cnt;
			chkMass(nr, nc, cnt);
		}
	}
}
int calMass(int cnt) {
	vector<int> v(cnt);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 1; k < cnt; k++) {
				if (visit[i][j] == k) v[k]++;
			}
		}
	}
	sort(v.begin(), v.end(), greater<>());
	return v[0];
}
int main() {
	cin >> n >> Q;
	N = pow(2, n);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	for (int q = 0; q < Q; q++) {
		int L;
		cin >> L;
		rotation(L);
		fireStorm();

	}
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] <= 0 || visit[i][j] > 0) continue;
			visit[i][j] = cnt;
			chkMass(i, j, cnt);
			cnt++;
		}
	}
	int ans = calMass(cnt);
	cout << remainIce() << "\n" << ans;

	return 0;
}