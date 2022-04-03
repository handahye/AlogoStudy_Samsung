#include <iostream>
#include <vector>
#include<algorithm>
#include<deque>
#include<list>
/*
#20056_마법사 상어와 파이어볼
i번 파이어볼의 위치는 (ri, ci), 질량은 mi이고, 방향은 di, 속력은 si이다.
1번부터 N번까지 번호가 매겨져 있고, 1번 행은 N번과 연결되어 있고, 1번 열은 N번 열과 연결되어 있다.
*/
using namespace std;
struct FIRE {
	int r, c, m, s, d;
};
int dr[] = { -1,-1,0,1,1,1,0,-1 };
int dc[] = { 0,1,1,1,0,-1,-1,-1 };
int N, M, K;
vector<FIRE> fireBall;
vector<FIRE> map[51][51];
void move() {
	vector<pair<int, int>> v;
	int fSize = fireBall.size();
	for (int i = 0; i < fSize; i++) {
		int r = fireBall[i].r;
		int c = fireBall[i].c;
		int m = fireBall[i].m;
		int s = fireBall[i].s;
		int d = fireBall[i].d;

		int nr = (r + dr[d] * s) % N;
		int nc = (c + dc[d] * s) % N;
		if (nr < 0) nr += N;
		if (nc < 0) nc += N;

		fireBall[i].r = nr;
		fireBall[i].c = nc;
	}
}
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j].clear();
		}
	}
}
void inserMap() {
	for (int i = 0; i < fireBall.size(); i++) {
		int r = fireBall[i].r;
		int c = fireBall[i].c;
		map[r][c].push_back(fireBall[i]);
	}
}
int main() {
	int sum = 0;
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		fireBall.push_back({ r - 1,c - 1,m,s,d });
	}
	for (int k = 0; k < K; k++) {
		move();
		init();
		inserMap();
		fireBall.clear();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j].size() == 0) continue;
				else if (map[i][j].size() == 1) {
					fireBall.push_back(map[i][j][0]);
				}
				else {
					int mSum = 0, sSum = 0;
					bool chkEven = true, chkOdd = true;

					for (FIRE fire : map[i][j]) {
						mSum += fire.m;
						sSum += fire.s;

						if (fire.d % 2 == 0) {
							chkOdd = false;
						}
						else {
							chkEven = false;
						}
					}
					int m = mSum / 5;
					int s = sSum / map[i][j].size();
					if (m == 0) continue;
					if (chkEven || chkOdd) {
						fireBall.push_back({ i,j,m,s,0 });
						fireBall.push_back({ i,j,m,s,2 });
						fireBall.push_back({ i,j,m,s,4 });
						fireBall.push_back({ i,j,m,s,6 });
					}
					else {
						fireBall.push_back({ i,j,m,s,1 });
						fireBall.push_back({ i,j,m,s,3 });
						fireBall.push_back({ i,j,m,s,5 });
						fireBall.push_back({ i,j,m,s,7 });
					}
				}
			}
		}

	}
	for (FIRE fire : fireBall) {
		sum += fire.m;
	}
	cout << sum << "\n";
	return 0;
}