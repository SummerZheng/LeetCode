#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include"print.h"

using namespace std;

class undirectedGraph {
  public:
    undirectedGraph(int _v = 0):v(_v){}
    undirectedGraph(int _v, vector<pair<int, int>>&edges):v(_v), adj(_v){
      for (const auto& p : edges) {
        adj[p.first].push_front(p.second);
        adj[p.second].push_front(p.first);
      }
    }
    int depth_first_search(int node, int depth_from_above) {
      int depth = 0;
      vector<bool> visited(v, false);
      queue<int> curLevel, nextLevel;
      curLevel.push(startN);
      visited[startN] = true; 
      while (!curLevel.empty()) {
        ++depth;
        while (!curLevel.empty()) {
          int nd = curLevel.front();
          curLevel.pop();
          for (const auto& n : adj[nd]) {
            if (visited[n] == false) {
              visited[n] = true;
              nextLevel.push(n);
            }
          }
        }
        swap(curLevel, nextLevel);
      }
      return depth-1;
    }

    vector<int> find_node_at_level(int i) {
      return level_tablet[i];
    }

  private:
    int v;
    vector<list<int>> adj;
    map<int, vector<int>> nodeT;
};

vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
  undirectedGraph myGraph(n, edges);
  int depth = myGraph.depth_first_search(0);
  cout<<"depth of the tree is "<<depth<<endl;
  vector<int> rootNode;
  if (depth%2 == 0) {
    rootNode = myGraph.find_node_at_level(depth/2);
  } else {
    rootNode = myGraph.find_node_at_level((depth-1)/2);
    vector<int> tmp(myGraph.find_node_at_level((depth+1)/2));
    rootNode.insert(rootNode.end(), tmp.begin(), tmp.end());
  }
  return rootNode;
}

int main() {
  vector<pair<int, int>> edges;
  edges.push_back(make_pair(1, 0));
  edges.push_back(make_pair(1, 2));
  edges.push_back(make_pair(1, 3));
  print(findMinHeightTrees(4, edges));
  return 0;
}
