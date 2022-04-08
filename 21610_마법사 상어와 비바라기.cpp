#include <iostream>
#include <vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
#include<cstring>
/*
#21610_마법사 상어와 비바라기
비바라기를 시전하면 (N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름이 생긴다
이제 구름에 이동을 M번 명령하려고 한다
*/
using namespace std;
int dr[] = { 0,-1,-1,-1,0,1,1,1 };
int dc[] = { -1,-1,0,1,1,1,0,-1 };
int N, M;
int map[51][51];
bool visit[51][51];
vector<pair<int, int>> cloud;
void chkCloud() {
	for (int k = 0; k < cloud.size(); k++) {
		pair<int, int> p = cloud[k];
		visit[p.first][p.second] = true;
	}
}
void moveCloud(int d, int s) {
	for (int i = 0; i < s; i++) {
		for (int k = 0; k < cloud.size(); k++) {
			int nr = cloud[k].first + dr[d];
			int nc = cloud[k].second + dc[d];

			if (nr == -1) nr = N - 1;
			else if (nr == N) nr = 0;
			if (nc == -1) nc = N - 1;
			else if (nc == N) nc = 0;

			cloud[k] = { nr,nc };
		}
	}
}
void rain() {
	for (int k = 0; k < cloud.size(); k++) {
		pair<int, int> p = cloud[k];
		map[p.first][p.second]++;
	}
}
void magic() {
	int rr[] = { -1,-1,1,1 };
	int cc[] = { -1,1,-1,1 };
	for (int k = 0; k < cloud.size(); k++) {
		pair<int, int> p = cloud[k];
		for (int d = 0; d < 4; d++) {
			int nr = p.first + rr[d];
			int nc = p.second + cc[d];
			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (map[nr][nc] > 0) map[p.first][p.second]++;
		}
	}
}
void makeClod() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] >= 2 && !visit[i][j]) {
				cloud.push_back({ i,j });
				map[i][j] -= 2;
			}
		}
	}
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	cloud.push_back({ N - 2, 0 });
	cloud.push_back({ N - 2, 1 });
	cloud.push_back({ N - 1, 0 });
	cloud.push_back({ N - 1, 1 });


	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		d--;
		moveCloud(d, s);
		chkCloud();
		rain();
		magic();
		cloud.clear();
		makeClod();
		memset(visit, false, sizeof(visit));
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > 0) ans += map[i][j];
		}
	}
	cout << ans << "\n";
	return 0;
}