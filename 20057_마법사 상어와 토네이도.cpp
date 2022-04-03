#include <iostream>
#include <vector>
#include<algorithm>
#include<deque>
#include<list>
/*
#20057_������ ���� ����̵�
 ��� ĭ���� ����̵��� �̵��� ���۵ȴ�. ����̵��� �� ���� �� ĭ �̵��Ѵ�.
 ����̵��� x���� y�� �̵��ϸ�, y�� ��� �𷡰� ������ �ᰡ �����ִ� ĭ���� �̵��Ѵ�.
   -  ������ �����ִ� ĭ���� �̵��ϴ� ���� ���� y�� �ִ� ���� �ش� ������ŭ�̰�, ��꿡�� �Ҽ��� �Ʒ��� ������.
   - ��� �̵��ϴ� ���� ���� ������ �����ִ� ĭ���� �̵����� ���� ���� ���� ��� ����. 
 �𷡰� �̹� �ִ� ĭ���� �𷡰� �̵��ϸ�, ���� ���� ��������.

  �𷡰� ������ ������ �̵��� ���� �ִ�. 
  ����̵��� �Ҹ�Ǿ��� ��, ������ ������ ���� ���� ���� ���غ���.
*/
using namespace std;
int N; 
int A[500][500];
int dr[] = { 0,1,0,-1 };
int dc[] = { -1,0,1,0 };
int calR[4][9] = { { -2, -1,-1,-1,0,1,1,1,2},{-1,-1,0,0,0,0,1,1,2}, 
	{-2,-1,-1,-1,0,1,1,1,2},{-2,-1,-1,0,0,0,0,1,1} };
int calC[4][9] = { {0,-1,0,1,-2,-1,0,1,0},{-1,1,-2,-1,1,2,-1,1,0} 
,{0,-1,0,1,2,-1,0,1,0} ,{0,-1,1,-2,-1,1,2,-1,1} };
double percent[4][9] = { {0.02, 0.1, 0.07, 0.01, 0.05, 0.1, 0.07, 0.01, 0.02},{0.01,0.01,0.02,0.07,0.07,0.02,0.1,0.1,0.05}
,{0.02,0.01,0.07,0.1,0.05,0.01,0.07,0.1,0.02},{0.05,0.1,0.1,0.02,0.07,0.07,0.02,0.01,0.01} };
int res = 0;
int cal(int r, int c, int d) {
	int amount = A[r][c];
	int ans = 0;
	for (int i = 0; i < 9; i++) {
		int nr = r + calR[d][i];
		int nc = c + calC[d][i];
		int sand = A[r][c] * percent[d][i];
		amount -= sand;
		//��� ���
		if (nr<1 || nc<1 || nr>N || nc>N) {
			ans += sand;
		}
		else {
			A[nr][nc] += sand;
		}
	}
	int R = r + dr[d];
	int C = c + dc[d];
	if (R<1 || C<1 || R>N || C>N) ans += amount;
	else A[R][C] +=amount;
	A[r][c] = 0;
	return ans;
}
bool move(int &r, int &c, int cnt, int s) {
	int d = cnt % 4;
	for (int i = 0; i < s; i++) {
		int nr = r + dr[d];
		int nc = c + dc[d];

		
		r = nr;
		c = nc;
		res+= cal(r, c, d);
		if (r == 1 && c == 1) return true;
	}
	return false;
	
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	int r = N / 2 + 1;
	int c = N / 2 + 1;
	int cnt = 0;
	int s = 0; //�������� �ϴ� Ƚ�� 
	//��, �Ʒ�, ����, ��
	while (1) {
		if (cnt % 2 == 0) s++;
		else if (cnt % 4 == 2) s++;
		if (move(r, c, cnt, s)) {
			break;
		}
		cnt++;
	}
	cout << res << "\n";
	return 0;
}