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
struct CUSTOMER{
  int startR, startC, endR, endC;
  bool departure;
};
struct DIST{
  int r, c, num;
};
bool compare(const DIST &a, const DIST &b){
  if(a.r!=b.r && b.c!=a.c) return a.r < b.r;
  else if(a.r==b.r) return a.c < b.c;
}
int N, M, total;
int taxiR, taxiC;
int map[21][21];
CUSTOMER customer[421];
int dr[]={0,0,1,-1};
int dc[]={1,-1,0,0};
int sDist;

void gotoDestination(int num, int r, int c, int rr, int cc, int dist, bool visit[][21]){
  if(rr==r && cc==c){
    if(sDist>dist){
      sDist = dist;
    }
    return;
  }
  for(int d=0; d<4; d++){
    int nr = r + dr[d];
    int nc = c + dc[d];

    if(nr<0 || nc<0 || nr>=N || nc>=N) continue;
    if(!visit[nr][nc]){
      visit[nr][nc] = true;
      gotoDestination(num, nr, nc, rr, cc, dist+1, visit);
      visit[nr][nc] = false;
    }
  }
  
}
bool chkCustomer(){
  for(int i=1; i<=M; i++){
    if(!customer[i].departure)return false;
  }
  return true;
}

int main()
{
  cin>>N>>M>>total;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      cin>>map[i][j];
    }
  }
  cin>>taxiR>>taxiC;
  for(int i=1; i<=M; i++){
    cin>> customer[i].startR >>customer[i].startC>>customer[i].endR>>customer[i].endC;
    customer[i].departure = false;
  }
  bool flag = false;
  while(1){
    if(chkCustomer()){
      flag = true;
      break;
    }
    vector<DIST> distInfo[421];
    int shortestDist=987654321; 
    bool visit[21][21];
    for(int i=1; i<=M; i++){
      if(customer[i].departure) continue;

      sDist = 987654321;
      visit[21][21] = {false,};
      visit[taxiR][taxiC] = true;
      //각 고객들의 최단 거리 구하기
      gotoDestination(i, taxiR, taxiC, customer[i].startR, customer[i].startC, 0, visit);
      //최단 거리 
      if(shortestDist<sDist){
        shortestDist = sDist;
      }
      distInfo[sDist].push_back({customer[i].startR, customer[i].startC, i});
    }

    if(distInfo[shortestDist].size()>1){
      sort(distInfo[shortestDist].begin(), distInfo[shortestDist].end(),compare);
    }
    int num = distInfo[shortestDist][0].num;
    taxiR = customer[num].startR;
    taxiC = customer[num].startC;
    
    sDist = 987654321;
    visit[21][21] = {false,};
    visit[taxiR][taxiC] = true;
    gotoDestination(num, taxiR, taxiC, customer[num].endR, customer[num].endC, 0, visit);
    int fuel = total - shortestDist - sDist; 
    if(fuel<0) break;
    total = fuel + (sDist*2);
    customer[num].departure = true;
  }
  if(flag) cout<<total<<"\n";
  else cout<<"-1";
	return 0;
}