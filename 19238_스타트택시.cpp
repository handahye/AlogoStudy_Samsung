#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
ㅇ 칸은 비어있거나 벽이 놓여 있음
ㅇ 택시가 빈칸에 있으면 -> 상,하,좌,우 인접한 빈칸 중 하나로 이동 가능 (최단 경로로만 이동)
ㅇ M명의 승객은 빈칸 중 하나에 서있으며 다른 칸빈 중 하나로 이동하려고 함. (여러 승객이 같이 탑승하진 않음)

ㅇ 택시 기사가 승객을 고를 때
   1. 현재 위치에서 최단 거리가 가장 짧은 승객 선택
       1-1. 여러명이면 행 번호가 가장 작은 승객을 (r)
          1-1-1. 그런 승객도 여러명이면 그중 열 번호가 가장 작은 승객 (c)
ㅇ 연료는 한 칸 이동할 때마다 1만큼 소요됨
      -> 한 승객을 목적지로 이동시키면 그 승객을 태워 이동하여 소모한 연료량 * 2 충전됨
      -> 그러나 이동에 실패하면 그 날의 업무가 끝남 (연료가 바닥다는 경우)


1) 택시로 부터 각 승객의 최단 거리 구해서 담기

구해야 할 것!
 -> 모든 승객을 성공적으로 데려다줄 수 있는지?
 -> 데려다줄 수 있는 경우 최종적으로 남는 연료의 양
*/
struct CUSTOMER {
    int startR, startC, endR, endC;
};
struct DIST {
    int r, c, dist, num;
};
bool compare(const DIST& a, const DIST& b) {
    if (a.dist < b.dist) return true;
    else if (a.dist == b.dist) {
        if (a.r < b.r) return true;
        else if (a.r == b.r) {
            if (a.c < b.c) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
int N, M, total;
int taxiR, taxiC;
int map[21][21];
CUSTOMER customer[421];
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
int sDist;
bool visit[21][21];
int num;
bool chk;
void shortestCustomer() {
    memset(visit, false, sizeof(visit));
    queue<pair<pair<int, int>, pair<int, int>>> que;
    que.push({ {taxiR,taxiC},{0,total} });
    visit[taxiR][taxiC] = true;
    vector<DIST> v;
    while (!que.empty()) {
        int r = que.front().first.first;
        int c = que.front().first.second;
        int dist = que.front().second.first;
        int fuel = que.front().second.second;
        que.pop();

        if (fuel < 0) continue;
        if (map[r][c] >= 1) {
            v.push_back({ r,c,dist,map[r][c] }); //손님이있음 
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
            if (map[nr][nc] != -1 && !visit[nr][nc]) {
                visit[nr][nc] = true;
                que.push({ {nr,nc},{dist + 1,fuel - 1} });
            }
        }
    }
    if (v.size() == 0) {
        num = -1;
        return;
    }
    sort(v.begin(), v.end(), compare);
    map[v[0].r][v[0].c] = 0;
    total = total - v[0].dist;
    num = v[0].num;
    return;

}
void bfs(int num, int tr, int tc, int cr, int cc) {
    memset(visit, false, sizeof(visit));
    queue<pair<pair<int, int>, pair<int, int>>> que;
    que.push({ {tr,tc},{0,total} }); //택시 위치, 거리, 연료량
    while (!que.empty()) {
        int r = que.front().first.first;
        int c = que.front().first.second;
        int dist = que.front().second.first;
        int fuel = que.front().second.second;
        que.pop();

        if (fuel < 0) return;
        if (r == cr && c == cc) {
            total -= dist;
            total += (dist * 2);
            taxiR = r;
            taxiC = c;
            chk = true;
            return;
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
            if (map[nr][nc] != -1 && !visit[nr][nc]) {
                visit[nr][nc] = true;
                que.push({ {nr,nc},{dist + 1, fuel - 1} });
            }
        }
    }
}

int main()
{
    cin >> N >> M >> total;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) map[i][j] = -1;
        }
    }
    cin >> taxiR >> taxiC;
    for (int i = 1; i <= M; i++) {
        cin >> customer[i].startR >> customer[i].startC >> customer[i].endR >> customer[i].endC;
        map[customer[i].startR][customer[i].startC] = i;
    }
    bool fail = false;
    for (int i = 1; i <= M; i++) {
        num = -1;
        chk = false;
        shortestCustomer();

        if (num == -1) {
            fail = true;
            break;
        }
        bfs(num, customer[num].startR, customer[num].startC, customer[num].endR, customer[num].endC);
        if (!chk) {
            fail = true;
            break;
        }

    }
    if (fail) cout << -1;
    else cout << total << "\n";
    return 0;
}