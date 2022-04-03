#include <iostream>
#include <vector>
#include<algorithm>
#include<deque>
/*
#20055_�����̾� ��Ʈ ���� �κ�
1 -> N -> N+1 -> 2N -> 1 ...
1�� ĭ�� �ִ� ��ġ�� "�ø��� ��ġ", N�� ĭ�� �ִ� ��ġ�� "������ ��ġ"
�� �κ��� �ø��� ��ġ���� �ø� �� �ִ�
�� �������� �κ��� ������ ��ġ�� �����ϸ� �� ��� ������
�� �κ��� �����̾� ��Ʈ ������ ������ �̵��� �� �ִ�
�� �κ��� �ø��� ��ġ�� �ø��ų� �κ��� � ĭ���� �̵��ϸ� �� ĭ�� �������� ��� 1��ŭ �����Ѵ�.

1. ��Ʈ�� �� ĭ ���� �ִ� �κ��� �Բ� �� ĭ ȸ���Ѵ�.
2. ���� ���� ��Ʈ�� �ö� �κ�����, ��Ʈ�� ȸ���ϴ� �������� �� ĭ �̵��� �� �ִٸ� �̵��Ѵ�.
   ���� �̵��� �� ���ٸ� ������ �ִ´�.
   2-1) �κ��� �̵��ϱ� ���ؼ��� �̵��Ϸ��� ĭ�� �κ��� ������,
		�� ĭ�� �������� 1 �̻� ���� �־�� �Ѵ�.
3. �ø��� ��ġ�� �ִ� ĭ�� �������� 0�� �ƴϸ� �ø��� ��ġ�� �κ��� �ø���.
4. �������� 0�� ĭ�� ������ K�� �̻��̶�� ������ �����Ѵ�. �׷��� �ʴٸ� 1������ ���ư���.
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
		belt.push_back(false); //���� �κ� �ִ��� Ȯ�� 
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