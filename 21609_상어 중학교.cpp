#include <iostream>
#include <vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
#include<cstring>
/*
#21609_상어 중학교
일반 블록은 M가지 색상이 있고, 색은 M이하의 자연수로 표현
검은색 블록은 -1, 무지개 블록은 0
블록 그룹은 연결된 블록의 집합
   ㅇ 그룹에는 일반 블록이 적어도 하나 있어야 하며, 일반 블록의 색은 모두 같아야 한다.
   ㅇ 검은색 블록은 포함되면 안 되고, 무지개 블록은 얼마나 들어있든 상관없다
   ㅇ 블록 그룹의 기준 블록은 무지개 블록이 아닌 블록 중에서 행의 번호가 가장 작은 블록, 
          그러한 블록이 여러개면 열의 번호가 가장 작은 블록이다.
*/
using namespace std;
struct NODE {
	int r, c;
};
struct BLOC {
	int r, c; 
	int total;
	vector<NODE> normal;
	vector<NODE> rainbow;
};
bool cmp1(NODE a, NODE b) {
	if (a.r < b.r) return true;
	else if (a.r == b.r) {
		if (a.c < b.c) return true;
		else return false;
	}
	else return false;
}
bool cmp2(BLOC a, BLOC b) {
	if (a.total > b.total) return true;
	else if (a.total == b.total) {
		if (a.rainbow.size() > b.rainbow.size()) return true;
		else if (a.rainbow.size() == b.rainbow.size()) {
			if (a.r > b.r) return true;
			else if (a.r == b.r) {
				if (a.c > b.c) return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}
int N, M;
int ans = 0;
int map[21][21];
bool visit[21][21] = { false, };
bool chkNum[6] = { false };
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
vector<NODE> normal, rainbow;
vector<BLOC> bloc;
void solve(int r, int c, int num) {
	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
		if (map[nr][nc] <=-1 || visit[nr][nc]) continue;

		if (map[nr][nc] == 0) {
			rainbow.push_back({ nr,nc });
			visit[nr][nc] = true;
			solve(nr, nc, num);
		}
		else if (map[nr][nc] == num) {
			normal.push_back({ nr,nc });
			visit[nr][nc] = true;
			solve(nr, nc, num);
		}

		
	}
}

bool findBigBlocGroup() {
	bool find = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num = map[i][j];
			if (num <= 0) continue; 
			memset(visit, false, sizeof(visit));
			normal.clear();
			rainbow.clear();
			normal.push_back({ i,j });
			visit[i][j] = true;
			solve(i, j, num);

			int total = normal.size() + rainbow.size();
			if (total >= 2) {
				sort(normal.begin(), normal.end(), cmp1);
				find = true;
				bloc.push_back({ normal[0].r, normal[0].c, total ,normal, rainbow });
			}
		}
	}
	return find;
}
int removeBloc() {
	int B = bloc[0].total;
	vector<NODE> node = bloc[0].normal;
	for (int i = 0; i < node.size(); i++) {
		int r = node[i].r;
		int c = node[i].c;
		map[r][c] = -2;
	}
	node = bloc[0].rainbow;
	for (int i = 0; i < node.size(); i++) {
		int r = node[i].r;
		int c = node[i].c;
		map[r][c] = -2;
	}
	return B * B;
}
void gravity() {
	//격자에 중력이 작용하면 검은색 블록을 제외한 모든 블록이 행의 번호가 큰 칸으로 이동한다.
	//이동은 다른 블록이나 격자의 경계를 만나기 전까지 계속 된다.
	for (int j = 0; j < N; j++) {
		stack<int> st;
		int black = -1;
		for (int i = 0; i < N; i++) {
			if (map[i][j] >= 0) {
				st.push(map[i][j]);
				map[i][j] = -2;
				if (i == N - 1) {
					int sSize = st.size();
					int cur = N - 1;
					for (int k = 0; k < sSize; k++) {
						map[cur][j] = st.top();
						st.pop();
						cur--;
					}
				}
			}
			else if (map[i][j] == -1) {
				int sSize = st.size();
				int cur = i - 1;
				for (int k = 0; k < sSize; k++) {
					int num = st.top();
					map[cur][j] = num;
					st.pop();
					cur--;
				}
			}
			else if (i == N - 1) {
				int sSize = st.size();
				int cur = N - 1;
				for (int k = 0; k < sSize; k++) {
					map[cur][j] = st.top();
					st.pop();
					cur--;
				}
			}
		}
	}
}
void rotation() {
	queue<int> q;
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= 0; j--) {
			q.push(map[i][j]);
		}
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			map[i][j] = q.front();
			q.pop();
		}
	}
}
void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	while (1) {
		if (!findBigBlocGroup()) break;
		sort(bloc.begin(), bloc.end(), cmp2);
		ans+=removeBloc();
		gravity();
		rotation();
		gravity();

		bloc.clear();
	}
	cout << ans << "\n";
	return 0;
}