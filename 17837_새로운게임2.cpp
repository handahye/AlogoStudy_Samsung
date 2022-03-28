#include <iostream>
#include <vector>
#include<deque>
/*
1. ��� ĭ�� ���
   1) �̵��Ϸ��� ĭ�� �̹� ���� �ִ� ��� ���� ���� A�� ���� ��
	  A, B, C �̵�, �̵��Ϸ��� ĭ�� D, E�� �ִ� ��� D, E, A, B, C
2. ���� ĭ�� ���
   1) A�� ���� ������ ��� ���� �׿� �ִ� ������ �ݴ�� �ٲ�
	 1-1) A, B, C �̵�, �̵��Ϸ��� ĭ�� ���� ���� ��� A, B, C -> C, B, A
	 1-2) A, D, F, G �̵�, �̵��Ϸ��� ĭ�� E, C ,B�� �ִ� ��� E, C
		  E, C ,B, G, F, D, A
3. �Ķ�ĭ�� ���
   1) �̵� ������ �ݴ�� �ϰ�, �̵��Ϸ��� ĭ�� �Ķ����̸� ������
4. ü���� ����� ���
   1) �̵� ���� �ٲٰ�, �̵��Ϸ��� ĭ�� �Ķ����̸� ������

���� ����: �� ĭ�� ���� 4�� �̻� �Ǵ� ��� ����!
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