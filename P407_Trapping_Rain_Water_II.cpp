#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int trapRainWater(vector<vector<int>>& heightMap) {
  if (heightMap.empty() || heightMap[0].empty()) return 0;
  int M = heightMap.size(), N = heightMap[0].size();
  vector<vector<int>> lmax(M, vector<int>(N, 0));
  vector<vector<int>> rmax(M, vector<int>(N, 0));
  vector<vector<int>> umax(M, vector<int>(N, 0));
  vector<vector<int>> dmax(M, vector<int>(N, 0));
  for (int i = 0; i < M; ++i) {
    lmax[i][0] = heightMap[i][0];
    rmax[i][N-1] = heightMap[i][N-1];
    for (int j = 1; j < N; ++j) {
      lmax[i][j] = heightMap[i][j] > lmax[i][j-1] ? heightMap[i][j] : lmax[i][j-1];
      rmax[i][N-1-j] = heightMap[i][N-1-j] > rmax[i][N-j] ? heightMap[i][N-1-j] : rmax[i][N-j];
    }
  }
  for (int j = 0; j < N; ++j) {
    umax[0][j] = heightMap[0][j];
    dmax[M-1][j] = heightMap[M-1][j];
    for (int i = 1; i < M; ++i) {
      umax[i][j] = heightMap[i][j] > umax[i-1][j] ? heightMap[i][j] : umax[i-1][j];
      dmax[M-1-i][j] = heightMap[M-1-i][j] > dmax[M-i][j] ? heightMap[M-1-i][j] : dmax[M-i][j];
    }
  }
  int wt = 0;
  vector<vector<int>> water(M, vector<int>(N, 0));
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      int haha = min(min(lmax[i][j], rmax[i][j]), min(umax[i][j], dmax[i][j])) - heightMap[i][j];
      water[i][j] = haha;
      wt += haha;
    }
  }
  cout<<"lmax"<<endl;
  print(lmax);
  cout<<"rmax"<<endl;
  print(rmax);
  cout<<"umax"<<endl;
  print(umax);
  cout<<"dmax"<<endl;
  print(dmax);
  cout<<"water"<<endl;
  print(water);
  return wt;
}

int main() {
  vector<vector<int>> htMap(
      {{12, 13, 1, 12}, 
       {13, 4, 13, 12},
       {13, 8, 10, 12},
       {12, 13, 12, 12},
       {13, 13, 13, 13}});
  cout<<trapRainWater(htMap)<<endl;
  return 0;
}
