#include <iostream>
#include <vector>
#include<deque>
/*
1. 흰색 칸인 경우
   1) 이동하려는 칸에 이미 말이 있는 경우 가장 위에 A번 말을 둠
	  A, B, C 이동, 이동하려는 칸에 D, E가 있는 경우 D, E, A, B, C
2. 빨간 칸인 경우
   1) A번 말과 그위의 모든 말의 쌓여 있는 순서를 반대로 바꿈
	 1-1) A, B, C 이동, 이동하려는 칸에 말이 없는 경우 A, B, C -> C, B, A
	 1-2) A, D, F, G 이동, 이동하려는 칸에 E, C ,B가 있는 경우 E, C
		  E, C ,B, G, F, D, A
3. 파란칸인 경우
   1) 이동 방향을 반대로 하고, 이동하려는 칸이 파란색이면 가만히
4. 체스판 벗어나는 경우
   1) 이동 방향 바꾸고, 이동하려는 칸이 파란색이면 가만히

종료 시점: 한 칸에 말이 4개 이상 되는 경우 종료!
*/
using namespace std;
struct MAP {
	int num;
	int d;
};
struct INFO {
	int r, c, dir;
};
int dr[] = { 0, 0,0,-1,1 };
int dc[] = { 0, 1,-1,0,0 };
deque<MAP> map[13][13];
vector<INFO> v;
int color[13][13];
int N, K;
int changeDir(int dir) {
	if (dir == 1) return 2;
	else if (dir == 2) return 1;
	else if (dir == 3) return 4;
	else if (dir == 4) return 3;
}
bool go(int color, int r, int c, int nr, int nc, int i) {
	if (color == 0) {
		bool flag = false;
		vector<pair<int, int>> tmp;
		for (int k = 0; k < map[r][c].size(); k++) {
			int num = map[r][c][k].num;
			int dir = map[r][c][k].d;
			tmp.push_back({ num, dir });
			if (map[r][c][k].num == i) {
				break;
			}
		}
		for (int k = tmp.size() - 1; k >= 0; k--) {
			int num = tmp[k].first;
			int dir = tmp[k].second;
			v[num].r = nr;
			v[num].c = nc;
			v[num].dir = dir;
			map[nr][nc].push_front({ num, dir });
			map[r][c].pop_front();
		}
	}
	else if (color == 1) {
		bool flag = false;
		int cur = -1;
		vector<pair<int, int>> tmp;
		for (int k = 0; k < map[r][c].size(); k++) {
			int num = map[r][c][k].num;
			int dir = map[r][c][k].d;
			tmp.push_back({ num, dir });
			if (map[r][c][k].num == i) {
				break;
			}
		}
		for (int k = 0; k < tmp.size(); k++) {
			int num = tmp[k].first;
			int dir = tmp[k].second;
			v[num].r = nr;
			v[num].c = nc;
			v[num].dir = dir;
			map[nr][nc].push_front({ num, dir });
			map[r][c].pop_front();
		}
	}
	if (map[nr][nc].size() >= 4) return false;
	else return true;
}
bool chkWall(int r, int c) {
	if (r <= 0 || c <= 0 || r > N || c > N) return true;
	return false;
}
int main() {
	int turn = 1;
	cin >> N >> K;
	v.resize(K + 1);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> color[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int r, c, dir;
		cin >> r >> c >> dir;
		map[r][c].push_back({ i, dir });
		v[i].r = r;
		v[i].c = c;
		v[i].dir = dir;
	}

	while (1) {
		if (turn > 1000) {
			turn = -1;
			break;
		}
		bool four = false;
		for (int i = 1; i <= K; i++) {
			//cout << "num: " << i << "\n";
			int r = v[i].r;
			int c = v[i].c;
			int dir = v[i].dir;

			int nr = r + dr[dir];
			int nc = c + dc[dir];

			if (chkWall(nr, nc) || color[nr][nc] == 2) {
				int num = -1;
				//cout << map[r][c].size() << "\n";
				for (int k = 0; k < map[r][c].size(); k++) {
					if (map[r][c][k].num == i) {
						num = k;
						break;
					}
				}
				dir = changeDir(dir);
				nr = r + dr[dir];
				nc = c + dc[dir];
				map[r][c][num].d = dir;
				v[i].dir = dir;
				if (chkWall(nr, nc) || color[nr][nc] == 2) {
					continue;
				}
			}
			if (!go(color[nr][nc], r, c, nr, nc, i)) {
				four = true;
				break;
			}
		}
		if (four) break;
		turn++;
		//cout << "turn: " << turn << "\n ";

	}
	cout << turn << "\n";
	return 0;
}