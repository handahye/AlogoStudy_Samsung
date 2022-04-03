#include <iostream>
#include <vector>
#include<algorithm>
#include<queue>
/*
#17825_주사위 윷놀이
 처음에는 시작 칸에 말 4개가 있다.
 말이 파란색 칸에서 이동을 시작하면 파란색 화살표를 타야 하고,
 이동하는 도중이거나 파란색이 아닌 칸에서 이동을 시작하면 빨간색 화살표를 타야 한다.
 도착 칸에 있지 않은 말을 하나 골라 주사위에 나온 수만큼 이동시킨다.
 말이 이동을 마치는 칸에 다른 말이 있으면 그 말은 고를 수 없다. (이동을 마치는 칸이 도착 칸이면 고를 수 있다.)

 주사위에서 나올 수 10개를 미리 알고 있을 때, 얻을 수 있는 점수의 최댓값을 구해보자.
*/
using namespace std;
int map[22] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40, -1 };
int blue1[14] = { 0,2,4,6,8,10,13,16,19,25,30,35,40,-1 }; //5
int blue2[18] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,25,30,35,40,-1 }; //10 
int blue3[24] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,28,27,26,25,30,35,40,-1 };//15
struct HORSE {
	int cur;
	int idx; //0 빨강  1, 2, 3 파랑
};
int sum = 0;
int dice[10];
vector<vector<int>> v;
int solve(vector<int> order) {
	vector<HORSE> horse;
	bool visit[4][24] = { false, };
	int total = 0;
	for (int i = 0; i < 4; i++) {
		horse.push_back({ 0,0 });
	}
	//25, 30 40에서 합쳐짐 

	for (int i = 0; i < order.size(); i++) {
		//cout << total << "\n";
		int num = order[i]; //현재 움직일 차례인 말 번호
		int cnt = dice[i]; //몇칸 움직여야 하는지 

		int cur = horse[num].cur; // 현재 움직여야 하는 말의 위치
		int idx = horse[num].idx; //현재 있는 말이 움직여야 하는 맵 

		int next = cur + cnt;

		if (cur == -1) return -1;

		if (idx == 0) {
			if (next >= 22) {
				visit[idx][cur] = false;
				horse[num].cur = -1;
				continue;
			}
			if (next == 5) {
				if (visit[1][next]) return -1;
				horse[num].idx = 1;
				total += blue1[next];
				horse[num].cur = next;
				visit[1][next] = true;
			}
			else if (next == 10) {
				if (visit[2][next]) return -1;
				horse[num].idx = 2;
				total += blue2[next];
				horse[num].cur = next;
				visit[2][next] = true;
			}
			else if (next == 15) {
				if (visit[3][next]) return -1;
				horse[num].idx = 3;
				total += blue3[next];
				horse[num].cur = next;
				visit[3][next] = true;
			}
			else {

				if (!visit[0][next]) {
					if (map[next] == 40) {
						if (visit[1][12] || visit[2][16] || visit[3][22])
							return -1;
					}
					total += map[next];
					horse[num].cur = next;
					visit[0][next] = true;
				}

			}

		}
		else if (idx == 1) {
			if (visit[idx][next]) return -1;
			if (next >= 14) {
				visit[idx][cur] = false;
				horse[num].cur = -1;
				continue;
			}
			if (blue1[next] == 40) {
				if (visit[0][20] || visit[2][16] || visit[3][22])
					return -1;
			}
			else if (blue1[next] == 35) {
				if (visit[2][15] || visit[3][21])
					return -1;
			}
			else if (blue1[next] == 30) {
				if (visit[2][14] || visit[3][20])
					return -1;
			}
			visit[idx][next] = true;
			total += blue1[next];
			horse[num].cur = next;
		}
		else if (idx == 2) {
			if (visit[idx][next]) return -1;
			if (next >= 18) {
				visit[idx][cur] = false;
				horse[num].cur = -1;
				continue;
			}
			if (blue2[next] == 40) {
				if (visit[0][20] || visit[1][12] || visit[3][22])
					return -1;
			}
			else if (blue2[next] == 35) {
				if (visit[1][11] || visit[3][21])
					return -1;
			}
			else if (blue2[next] == 30) {
				if (visit[1][10] || visit[3][20])
					return -1;
			}
			visit[idx][next] = true;
			total += blue2[next];
			horse[num].cur = next;
		}
		else {
			if (visit[idx][next]) return -1;
			if (next >= 24) {
				visit[idx][cur] = false;
				horse[num].cur = -1;
				continue;
			}
			if (blue3[next] == 40) {
				if (visit[0][20] || visit[1][12] || visit[2][16])
					return -1;
			}
			else if (blue3[next] == 35) {
				if (visit[1][11] || visit[2][15])
					return -1;
			}
			else if (blue3[next] == 30) {
				if (visit[1][10] || visit[2][14])
					return -1;
			}
			visit[idx][next] = true;
			total += blue3[next];
			horse[num].cur = next;
		}
		visit[idx][cur] = false;
	}
	//	cout << total << "\n";
	return total;
}
void decideOrder(int cnt, vector<int> order) {
	if (cnt == 10) {
		v.push_back(order);
		return;
	}
	for (int i = 0; i < 4; i++) {
		order.push_back(i);
		decideOrder(cnt + 1, order);
		order.pop_back();
	}
}
int main() {

	//말 움직일 순서 조합
	vector<int> order;
	decideOrder(0, order);
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}
	for (int i = 0; i < v.size(); i++) {
		//		cout << v[i].size() << "\n";
		int total = solve(v[i]);
		if (total == -1) continue;

		if (total > sum) sum = total;

	}
	cout << sum << "\n";
	return 0;
}