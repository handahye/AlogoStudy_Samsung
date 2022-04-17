
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <queue>
#include<sstream>
#include<cmath>
using namespace std;
/*
#21611_������ ���� ���ڵ�
���� ó���� �� �ִ� ĭ�� ������ ������ ĭ���� ������ �ϳ� �� �� �ִ�.
1. ��� ���� ����
2. ���� � ĭ A�� ��ȣ���� ��ȣ�� �ϳ� ���� ĭ�� �� ĭ�̸�, A�� �ִ� ������ �� �� ĭ���� �̵��Ѵ�.
3. �����ϴ� ������ 4�� �̻� �����ϴ� ������ ���� �� �߻��Ѵ�.
4. ���� �̵� -> ���� �����ϸ� ���� -> ...
5. ���� ��ȭ ! -> �����ϴ� ������ �ϳ��� �׷� //������ ����, ������ ��ȣ
	(����, ������ ĭ�� ������ ���� ĭ�� ���� ���ϴ� ��� �׷��� ������ �������.)

���ؾ� �ϴ� ��: 1��(������ 1�� ������ ����) + 2��(������ 2�� ������ ����) + 3��(������ 3�� ������ ����)


*/
struct NODE {
	int r, c, num;
};
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int map[51][51];
int M, N;
int ans[4] = { 0, };
void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}
void throwMarble(int d, int s, int sr, int sc) {
	for (int k = 1; k <= s; k++) {
		int nr = sr + (dr[d] * k);
		int nc = sc + (dc[d] * k);

		if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
			map[nr][nc] = -1;
		}
	}
}
void moveMarble(int sr, int sc) {
	int r = sr, c = sc;
	int rr[] = { 0,1,0,-1 };
	int cc[] = { -1,0,1,0 };
	queue<int> q;
	int cnt = 1;
	bool flag = false;
	while (1) {
		for (int d = 0; d < 2; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] >= 0)
						q.push(map[nr][nc]);
					map[nr][nc] = 0;
				}
				else {
					flag = true;
					break;
				}
				sr = nr;
				sc = nc;
			}
			if (flag) break;
		}
		if (flag) break;
		cnt++;

		for (int d = 2; d < 4; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] >= 0)
						q.push(map[nr][nc]);
					map[nr][nc] = 0;
				}
				sr = nr;
				sc = nc;
			}
		}
		cnt++;
	}
	cnt = 1;
	sr = r, sc = c;
	flag = false;
	while (!q.empty()) {
		for (int d = 0; d < 2; d++) {
			for (int k = 1; k <= cnt; k++) {
				if (q.empty()) {
					flag = true;
					break;
				}
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					map[nr][nc] = q.front();
					q.pop();
				}
				else {
					flag = true;
					break;
				}
				sr = nr;
				sc = nc;
				//print();
			}
			if (flag) break;
		}
		if (flag) break;
		cnt++;
		for (int d = 2; d < 4; d++) {
			for (int k = 1; k <= cnt; k++) {
				if (q.empty()) {
					flag = true;
					break;
				}
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					map[nr][nc] = q.front();
					q.pop();
				}
				sr = nr;
				sc = nc;
				//print();
			}
		}
		cnt++;
	}
}
bool findExplosion(int sr, int sc) {
	int x = sr, y = sc;
	bool find = false;
	int rr[] = { 0,1,0,-1 };
	int cc[] = { -1,0,1,0 };

	queue<NODE> q;
	int cnt = 1;
	bool flag = false;
	while (1) {
		for (int d = 0; d < 2; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] > 0)
						q.push({ nr,nc,map[nr][nc] });
				}
				else {
					flag = true;
					break;
				}
				sr = nr;
				sc = nc;
			}
			if (flag) break;
		}
		if (flag) break;
		cnt++;
		for (int d = 2; d < 4; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] > 0)
						q.push({ nr,nc,map[nr][nc] });
				}
				sr = nr;
				sc = nc;
			}
		}
		cnt++;
	}
	if (q.empty()) return find;
	vector<NODE> v[4];
	NODE cur = q.front();
	q.pop();
	cnt = 1;
	v[cur.num].push_back(cur);
	sr = x, sc = y;
	flag = false;
	while (!q.empty()) {
		NODE next = q.front();
		q.pop();
		if (next.num == cur.num) {
			cnt++;
			v[next.num].push_back(next);
		}
		else {
			if (cnt >= 4) {
				ans[cur.num] += (cur.num * v[cur.num].size());
				for (int k = 0; k < v[cur.num].size(); k++) {
					int r = v[cur.num][k].r;
					int c = v[cur.num][k].c;
					map[r][c] = -1;
				}
				find = true;
			}
			v[cur.num].clear();
			cur = next;
			cnt = 1;
			v[cur.num].push_back(cur);
		}

	}
	if (!find && cnt >= 4) {
		ans[cur.num] += (cur.num * v[cur.num].size());
		for (int k = 0; k < v[cur.num].size(); k++) {
			int r = v[cur.num][k].r;
			int c = v[cur.num][k].c;
			map[r][c] = -1;
		}
		find = true;
	}
	return find;
}
void changeMarble(int sr, int sc) {
	int r = sr, c = sc;
	int rr[] = { 0,1,0,-1 };
	int cc[] = { -1,0,1,0 };
	queue<NODE> q;
	int cnt = 1;
	bool flag = false;
	while (1) {
		for (int d = 0; d < 2; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] > 0)
						q.push({ nr,nc,map[nr][nc] });
					map[nr][nc] = 0;
				}
				else {
					flag = true;
					break;
				}
				sr = nr;
				sc = nc;
				//print();
			}
			if (flag) break;
		}
		if (flag) break;
		cnt++;
		for (int d = 2; d < 4; d++) {
			for (int k = 1; k <= cnt; k++) {
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					if (map[nr][nc] > 0)
						q.push({ nr,nc,map[nr][nc] });
					map[nr][nc] = 0;
				}
				sr = nr;
				sc = nc;
				//print();
			}
		}
		cnt++;
	}
	sr = r, sc = c;
	if (q.empty()) return;
	NODE cur = q.front();
	q.pop();
	cnt = 1;
	vector<int> v;

	while (!q.empty()) {
		NODE next = q.front();
		q.pop();
		if (next.num == cur.num) {
			cnt++;
		}
		else {
			v.push_back(cnt);
			v.push_back(cur.num);
			cur = next;
			cnt = 1;
		}
	}
	v.push_back(cnt);
	v.push_back(cur.num);

	cnt = 1;
	flag = false;
	int idx = 0;
	sr = r, sc = c;
	while (1) {
		for (int d = 0; d < 2; d++) {
			for (int k = 1; k <= cnt; k++) {
				if (idx >= v.size()) {
					flag = true;
					break;
				}
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					map[nr][nc] = v[idx++];
				}
				else {
					flag = true;
					break;
				}
				sr = nr;
				sc = nc;
			}
			if (flag) break;
		}
		if (flag) break;
		cnt++;
		for (int d = 2; d < 4; d++) {
			for (int k = 1; k <= cnt; k++) {
				if (idx >= v.size()) {
					flag = true;
					break;
				}
				int nr = sr + rr[d];
				int nc = sc + cc[d];
				if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
					map[nr][nc] = v[idx++];
				}
				sr = nr;
				sc = nc;
			}
		}
		cnt++;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	int sr = (N + 1) / 2, sc = (N + 1) / 2;
	sr--, sc--;
	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		d--;
		throwMarble(d, s, sr, sc);
		//print();
		moveMarble(sr, sc);
		//print();
		while (1) {
			bool canExplosion = findExplosion(sr, sc);
			//print();
			if (!canExplosion) break;
			moveMarble(sr, sc);
			//print();
		}
		changeMarble(sr, sc);
		//print();
	}
	int total = 0;
	for (int i = 1; i < 4; i++) total += ans[i];
	cout << total;
	return 0;
}