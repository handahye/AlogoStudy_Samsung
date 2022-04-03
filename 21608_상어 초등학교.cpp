#include <iostream>
#include <vector>
#include<algorithm>
#include<functional>
#include<queue>
#include<cmath>
/*
#21608_상어 초등학교
*/
using namespace std;
int N;
int student[450][4];
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0, };
int map[21][21];
struct NODE {
	int r, c, like, adj;
};
bool cmp(NODE a, NODE b) {
	if (a.like > b.like) return true;
	else if (a.like == b.like) {
		if (a.adj > b.adj) return true;
		else if (a.adj == b.adj) {
			if (a.c < b.c) return true;
			else if (a.c == b.c) {
				if (a.r < b.r)return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}
int main() {
	cin >> N;
	for (int k = 1; k <= N * N; k++) {
		int num;
		cin >> num;
		cin >> student[num][0] >> student[num][1] >> student[num][2] >> student[num][3];
		vector<NODE> v;
		//인접한 칸 체크
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][j] > 0) continue; //이미 학생이 있으면 못 앉음
				int like = 0, adj = 0;

				for (int d = 0; d < 4; d++) { //현재 자리에서 인접한 자리 체크
					int nr = i + dr[d];
					int nc = j + dc[d];
					if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
					if (map[nr][nc] == 0) adj++; //비어있는 자리 
					else {
						for (int l = 0; l < 4; l++) { //내가 좋아하는 학생 체크
							if (map[nr][nc] == student[num][l]) {
								like++;
							}
						}
					}

				}
				v.push_back({ i,j,like,adj });
			}
		}
		sort(v.begin(), v.end(), cmp);
		int r = v[0].r;
		int c = v[0].c;
		map[r][c] = num;
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num = map[i][j];
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nr = i + dr[d];
				int nc = j + dc[d];
				if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
				int cur = map[nr][nc];
				for (int k = 0; k < 4; k++) {
					if (student[num][k] == cur) cnt++;
				}
			}
			if (cnt == 1) ans += 1;
			else if (cnt == 2) ans += 10;
			else if (cnt == 3) ans += 100;
			else if (cnt == 4) ans += 1000;
		}
	}
	cout << ans;
	return 0;
}