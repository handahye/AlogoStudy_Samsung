#include <iostream>
#include <vector>
#include<algorithm>
#include<queue>
/*
#17825_�ֻ��� ������
 ó������ ���� ĭ�� �� 4���� �ִ�.
 ���� �Ķ��� ĭ���� �̵��� �����ϸ� �Ķ��� ȭ��ǥ�� Ÿ�� �ϰ�,
 �̵��ϴ� �����̰ų� �Ķ����� �ƴ� ĭ���� �̵��� �����ϸ� ������ ȭ��ǥ�� Ÿ�� �Ѵ�.
 ���� ĭ�� ���� ���� ���� �ϳ� ��� �ֻ����� ���� ����ŭ �̵���Ų��.
 ���� �̵��� ��ġ�� ĭ�� �ٸ� ���� ������ �� ���� �� �� ����. (�̵��� ��ġ�� ĭ�� ���� ĭ�̸� �� �� �ִ�.)

 �ֻ������� ���� �� 10���� �̸� �˰� ���� ��, ���� �� �ִ� ������ �ִ��� ���غ���.
*/
using namespace std;
int map[22] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40, -1 };
int blue1[14] = { 0,2,4,6,8,10,13,16,19,25,30,35,40,-1 }; //5
int blue2[18] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,25,30,35,40,-1 }; //10 
int blue3[24] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,28,27,26,25,30,35,40,-1 };//15
struct HORSE {
	int cur;
	int idx; //0 ����  1, 2, 3 �Ķ�
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
	//25, 30 40���� ������ 

	for (int i = 0; i < order.size(); i++) {
		//cout << total << "\n";
		int num = order[i]; //���� ������ ������ �� ��ȣ
		int cnt = dice[i]; //��ĭ �������� �ϴ��� 

		int cur = horse[num].cur; // ���� �������� �ϴ� ���� ��ġ
		int idx = horse[num].idx; //���� �ִ� ���� �������� �ϴ� �� 

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

	//�� ������ ���� ����
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