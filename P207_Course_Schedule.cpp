#include<iostream>
#include<vector>
#include"Graph/Graph.h"
#include"Graph/Graph.cpp"

using namespace std;

bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
  Graph myGraph(numCourses);
  for (auto const &ePair : prerequisites) {
    myGraph.addEdge(ePair);
  }
  return myGraph.topological_sort_inDegree();
}

int main() {
  int n = 2;
  vector<pair<int, int>> myVec;
  myVec.push_back(make_pair(0, 1));
  //myVec.push_back(make_pair(1, 0));
  cout<<canFinish(n, myVec)<<endl;
  return 0;
}
