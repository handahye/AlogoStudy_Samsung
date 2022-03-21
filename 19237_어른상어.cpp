#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
#19236 청소년 상어
상어가 먹을 수 있는 최대 물고기 수 구하기~
1) 물고기 이동
   - 물고기는 번호가 작은 순서로 움직 움직
   - 만약 상어랑 만나거나 map 벗어나면 반시계 방향으로 45도 각도 틈
	 (1) 이동 가넝하면 그 물고기랑 자리 체인지
	 (2) 이동 안되면 그 자리에 가마니~~~
	- 해당 방향으로 이동 가능하면 그 자리에 있는 물고기랑 자리 바꿩
2) 상어 이동
   - 해당 방향으로 여러칸 이동 가능~~~! (전부 다 따져야 함)
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
	int dir = fish[eatNum].dir; //상어 이동 방향 
	fish[eatNum].isDead = true;
	map[r][c] = 0;
	//물고기 이동
	for (int i = 1; i <= 16; i++) {
		if (!fish[i].isDead) {
			int dd = fish[i].dir;
			int rr = fish[i].r;
			int cc = fish[i].c;
			for (int d = 0; d < 8; d++) {
				int nr = rr + dr[dd];
				int nc = cc + dc[dd];
				if (nr < 0 || nc < 0 || nr >= 4 || nc >= 4) { // 맵 벗어나면 
					dd++;
					if (dd == 9) {
						dd = 1;
					}
					fish[i].dir = dd;
					continue;
				}
				if (nr == r && nc == c) { //상어 자리면 
					dd++;
					if (dd == 9) dd = 1;
					fish[i].dir = dd;
					continue;
				}

				if (map[nr][nc] == 0) { //옮기려는 자리에 물고기 없는 경우 
					map[nr][nc] = i;
					map[rr][cc] = 0;
					fish[i].r = nr;
					fish[i].c = nc;
					break;
				}
				else { // 물고기리기 자리 바꿈 
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

	//상어 이동
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