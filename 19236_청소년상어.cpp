#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
#19236 û�ҳ� ���
�� ���� �� �ִ� �ִ� ����� �� ���ϱ�~
1) ����� �̵�
   - ������ ��ȣ�� ���� ������ ���� ����
   - ���� ���� �����ų� map ����� �ݽð� �������� 45�� ���� ƴ
	 (1) �̵� �����ϸ� �� ������ �ڸ� ü����
	 (2) �̵� �ȵǸ� �� �ڸ��� ������~~~
	- �ش� �������� �̵� �����ϸ� �� �ڸ��� �ִ� ������ �ڸ� �ٲ�
2) ��� �̵�
   - �ش� �������� ����ĭ �̵� ����~~~! (���� �� ������ ��)
*/
int res = 0;
struct Fish {
	int r, c, dir;
	bool isDead;
};
int dr[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
void fishCopy(Fish dest[17], Fish src[17]) {
	for (int i = 1; i <= 16; i++) {
		dest[i] = src[i];
	}
}
void mapCopy(int dest[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			dest[i][j] = src[i][j];
}
void dfs(Fish org_fish[17], int org_map[4][4], int r, int c, int sum) {
	if (res < sum)res = sum;
	int map[4][4];
	Fish fish[17];

	fishCopy(fish, org_fish);
	mapCopy(map, org_map);

	int eatNum = map[r][c];
	int dir = fish[eatNum].dir; //��� �̵� ���� 
	fish[eatNum].isDead = true;
	map[r][c] = 0;
	//����� �̵�
	for (int i = 1; i <= 16; i++) {
		if (!fish[i].isDead) {
			int dd = fish[i].dir;
			int rr = fish[i].r;
			int cc = fish[i].c;
			for (int d = 0; d < 8; d++) {
				int nr = rr + dr[dd];
				int nc = cc + dc[dd];
				if (nr < 0 || nc < 0 || nr >= 4 || nc >= 4) { // �� ����� 
					dd++;
					if (dd == 9) {
						dd = 1;
					}
					fish[i].dir = dd;
					continue;
				}
				if (nr == r && nc == c) { //��� �ڸ��� 
					dd++;
					if (dd == 9) dd = 1;
					fish[i].dir = dd;
					continue;
				}

				if (map[nr][nc] == 0) { //�ű���� �ڸ��� ����� ���� ��� 
					map[nr][nc] = i;
					map[rr][cc] = 0;
					fish[i].r = nr;
					fish[i].c = nc;
					break;
				}
				else { // ����⸮�� �ڸ� �ٲ� 
					int tmpNum = map[nr][nc];
					map[nr][nc] = map[rr][cc];
					fish[i].r = nr;
					fish[i].c = nc;
					fish[i].dir = dd;

					map[rr][cc] = tmpNum;
					fish[tmpNum].r = rr;
					fish[tmpNum].c = cc;
					break;
				}

			}
		}

	}

	//��� �̵�
	int rr = r + dr[dir];
	int cc = c + dc[dir];
	while (rr >= 0 && cc >= 0 && rr < 4 && cc < 4) {
		if (map[rr][cc] != 0) {
			dfs(fish, map, rr, cc, sum + map[rr][cc]);
		}
		rr += dr[dir];
		cc += dc[dir];
	}
	return;
}
int main()
{
	Fish fish[17];
	int map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int num, dir;
			cin >> num >> dir;
			fish[num].r = i;
			fish[num].c = j;
			fish[num].dir = dir;
			map[i][j] = num;
			fish[num].isDead = false;
		}
	}
	dfs(fish, map, 0, 0, map[0][0]);
	cout << res;
	return 0;
}