#include <iostream>
#include <vector>
#include<algorithm>
#include<deque>
/*
#20055_컨베이어 벨트 위의 로봇
1 -> N -> N+1 -> 2N -> 1 ...
1번 칸이 있는 위치를 "올리는 위치", N번 칸이 있는 위치를 "내리는 위치"
ㅇ 로봇은 올리는 위치에만 올릴 수 있다
ㅇ 언제든지 로봇이 내리는 위치에 도달하면 그 즉시 내린다
ㅇ 로봇은 컨베이어 벨트 위에서 스스로 이동할 수 있다
ㅇ 로봇을 올리는 위치에 올리거나 로봇이 어떤 칸으로 이동하면 그 칸의 내구도는 즉시 1만큼 감소한다.

1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.
   만약 이동할 수 없다면 가만히 있는다.
   2-1) 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며,
		그 칸의 내구도가 1 이상 남아 있어야 한다.
3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
*/
using namespace std;
int N, K;
deque<int> A;
deque<bool> belt;
void rotate() {
	belt.push_front(belt.back());
	belt.pop_back();
	belt[N - 1] = false;

	A.push_front(A.back());
	A.pop_back();

}
void move() {
	for (int i = N - 2; i >= 0; i--) {
		if (!belt[i + 1] && A[i + 1] > 0 && belt[i]) {
			belt[i] = false;
			belt[i + 1] = true;
			A[i + 1]--;
		}
	}
	belt[N - 1] = false;
}
void robot() {
	if (!belt[0] && A[0] > 0) {
		belt[0] = true;
		A[0]--;
	}
}
int chk() {
	int cnt = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (A[i] == 0) cnt++;
	}
	return cnt;
}
int main() {
	cin >> N >> K;

	for (int i = 0; i < 2 * N; i++) {
		int a;
		cin >> a;
		A.push_back(a);
		belt.push_back(false); //위에 로봇 있는지 확인 
	}
	int res = 1;
	while (1) {
		rotate();
		move();
		robot();

		if (chk() >= K) {
			cout << res << "\n";
			return 0;
		}
		res++;
	}
	return 0;
}