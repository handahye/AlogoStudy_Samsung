#include <iostream>
#include <vector>
#include<algorithm>
#include<queue>
/*
#17822 원판 돌리기
인접한게 있는 경우 -> 지움
인접한게 없는 경우 -> 평균보다 작은 수는 +1, 큰수는 -1
*/
using namespace std;
int N, M, T;
int map[101][101];
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
struct QUEUE {
	int r, c, num;
};
void rotation(int dir, int r) {
	if (dir == 0) {
		int tmp = map[r][M];
		for (int c = M; c >= 1; c--) {
			if (c == 1) {
				map[r][c] = tmp;
				break;
			}
			map[r][c] = map[r][c - 1];
		}
	}//시계
	else if (dir == 1) {
		int tmp = map[r][1];
		for (int c = 1; c <= M; c++) {
			if (c == M) {
				map[r][c] = tmp;
				break;
			}
			map[r][c] = map[r][c + 1];
		}
	}//반시계
}
bool find() {
	bool flag = false;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == -1) continue;
			queue<QUEUE> q;
			int visit[101][101] = { 0, };
			q.push({ i,j , map[i][j] });
			visit[i][j] = 1;
			while (!q.empty()) {
				int r = q.front().r;
				int c = q.front().c;
				int num = q.front().num;
				q.pop();

				for (int d = 0; d < 4; d++) {
					int nr = r + dr[d];
					int nc = c + dc[d];

					if (d == 0 && nc == M + 1) nc = 1;
					else if (d == 1 && nc == 0) nc = M;

					if (!visit[nr][nc] && map[nr][nc] > 0) {
						if (num == map[nr][nc]) {
							//cout << "r: " << r << " c: " << c << "  nr: " << nr << " nc: " << nc << "\n";
							visit[nr][nc] = 1;
							map[r][c] = map[nr][nc] = -1;
							flag = true;
							q.push({ nr,nc,num });
						}
					}
				}

			}
		}
	}
	return flag;
}
void calAvg() {
	float sum = 0, cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != -1) {
				sum += map[i][j];
				cnt++;
			}
		}
	}
	float avg = sum / cnt;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != -1) {
				if (map[i][j] < avg) map[i][j]++;
				else if (map[i][j] > avg)map[i][j]--;
			}
		}
	}
}
int res() {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != -1) {
				sum += map[i][j];
			}
		}
	}
	return sum;
}
int main() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < T; i++) {
		int x, d, k;
		cin >> x >> d >> k;//2 4 6 8
		int r = x;
		for (int mul = 1; r <= N; mul++) {
			r = x * mul;
			for (int b = 0; b < k; b++) {
				rotation(d, r);
			}
		}
		//인접한 부분 찾기
		if (!find()) {
			calAvg();
		}
	}
	cout << res() << "\n";
	return 0;
}