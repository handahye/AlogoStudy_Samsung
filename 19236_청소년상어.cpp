#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
- 1�� ��ȣ�� ���� ���� ��� ���ѱ� ����
- �� ó������ ��� �� �ڽ��� ��ġ�� �ڽ��� ������ �Ѹ�
- 1�ʸ��� ��� �� �����¿� ������ ĭ���� �̵��ϰ�, �ڽ��� ������ �Ѹ�
- ������ �� k�� �̵��Ŀ� �����

- �̵� ���� ���� ���
   1) ������ ĭ �� �ƹ����� ���� ĭ����
   2) �׷�ĭ�� ������ �ڽ��� ������ �ִ� ĭ����
	  --> ���� Ư�� �켱������ �־ �װ� ������ ��


- ��� �� �̵��� �Ŀ� �� ĭ�� ���� ������ �� ���� ������ ���� ���� ��ȣ�� ���� �� �����ϰ�
��� ���� ������ �Ѱܳ� !

- 1�� �� ���ڿ� ���� �Ǳ���� ����?

1: ��, 2: �Ʒ�, 3:��, 4:��

*/
int dr[] = { 0,-1,1,0,0 };
int dc[] = { 0,0,0,-1,1 };

struct SHARK {
	int r, c, dir;
	bool isDead;
	vector<int> priority[5];
};
struct MAP {
	vector<int> v;
	int smellTime;
	int smellShark;
};
MAP map[21][21];
SHARK shark[410];
int N, M, k;
bool chk() {
	for (int i = 2; i <= M; i++) {
		if (!shark[i].isDead) return false;
	}
	return true;
}
void spreadSmell(int time) {
	for (int i = 1; i <= M; i++) {
		if (shark[i].isDead)continue;
		int r = shark[i].r;
		int c = shark[i].c;
		map[r][c].smellTime = time + k;
		map[r][c].smellShark = i;
	}
}
void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j].smellShark << "\t" << map[i][j].smellTime << "\t";
		}
		cout << "\n";
	}
	cout << "--------------------------------------\n\n";
}
void moveShark(int time) {
	for (int i = 1; i <= M; i++) {
		if (shark[i].isDead) continue;
		int r = shark[i].r;
		int c = shark[i].c;
		map[r][c].v.clear();
	}
	for (int i = 1; i <= M; i++) {
		cout << "time: " << time << "\n";
		print();
		if (shark[i].isDead) continue;
		int r = shark[i].r;
		int c = shark[i].c;
		int dir = shark[i].dir;
		cout << "r: " << r << " c: " << c << " dir: " << dir << "\n";
		int mr, mc, mdir;
		mr = mc = mdir = -1;
		bool flag = false;

		for (int j = 0; j < 4; j++) {
			int ndir = shark[i].priority[dir][j];
			int nr = r + dr[ndir];
			int nc = c + dc[ndir];
			cout << "ndir: " << ndir << " j: " << j << " num:  " << i << "\n";
			cout << "nr: " << nr << " nc: " << nc << "\n";
			if (nr >= 0 && nc >= 0 && nr < N && nc < N) {
				if (map[nr][nc].smellTime <= time) {
					flag = true;
					map[nr][nc].v.push_back(i);
					shark[i].r = nr;
					shark[i].c = nc;
					shark[i].dir = ndir;
					break;
				}
				else {
					if (map[nr][nc].smellShark == i) {
						if (mr == -1) {
							mr = nr;
							mc = nc;
							mdir = ndir;
						}
					}
				}
			}
		}
		if (!flag) {
			cout << "mdir: " << mdir << " mr: " << mr << " mc: " << mc << "\n";
			map[mr][mc].v.push_back(i);
			shark[i].r = mr;
			shark[i].c = mc;
			shark[i].dir = mdir;
		}
	}
}
void eatShark() {
	for (int i = 1; i <= M; i++) {
		if (shark[i].isDead) continue;
		int r = shark[i].r;
		int c = shark[i].c;
		//sort(map[r][c].v.begin(), map[r][c].v.end());
		if (map[r][c].v.size() > 2) {
			int winShark = map[r][c].v[0];
			for (int j = 1; j < map[r][c].v.size(); j++) {
				int num = map[r][c].v[j];
				shark[num].isDead = true;
			}
			map[r][c].v.clear();
			map[r][c].v.push_back(winShark);
			map[r][c].smellShark = winShark;
		}
	}
}
int main()
{
	cin >> N >> M >> k;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num;
			cin >> num;
			if (num > 0) {
				map[i][j].v.push_back(num);
				shark[num].r = i;
				shark[num].c = j;
			}
			map[i][j].smellTime = 0;
			map[i][j].smellShark = 0;
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> shark[i].dir;
		//cout << "shark num: " << i << " dir: " << shark[i].dir << "\n";
		shark[i].isDead = false;
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			int arr[4];
			cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
			for (int k = 0; k < 4; k++) {
				shark[i].priority[j].push_back(arr[k]);
				//cout << shark[i].priority[j][k] << "\n";
			}
		}
	}

	for (int time = 0; time <= 1000; time++) {
		if (chk()) {
			cout << time;
			return 0;
		}
		spreadSmell(time);
		moveShark(time);
		eatShark();
	}
	cout << "-1";
	return 0;
}