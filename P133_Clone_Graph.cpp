#include<iostream>
#include<unordered_map>
#include<queue>

using namespace std;

// Definition for undirected graph.
struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x) {};
};

UndirectedGraphNode* clone_if_not_exist(UndirectedGraphNode* oriN, 
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& myMap) {
  auto iter = myMap.find(oriN);
  if (iter == myMap.end()) {
    UndirectedGraphNode* cloneN = new UndirectedGraphNode(oriN->label);
    iter = myMap.emplace(oriN, cloneN).first;
  }
  return iter->second;
}

UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
  if (node==nullptr) return nullptr;
  unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> myMap;
  queue<UndirectedGraphNode*> nodeQ;
  nodeQ.push(node);
  while (!nodeQ.empty()) {
    UndirectedGraphNode* oriN = nodeQ.front();
    UndirectedGraphNode* cloneN = clone_if_not_exist(oriN, myMap);
    for (auto& nb : oriN->neighbors) {
      if (myMap.find(nb) == myMap.end())
        nodeQ.push(nb);
      cloneN->neighbors.push_back(clone_if_not_exist(nb, myMap));
    }
    nodeQ.pop(); 
  }
  return myMap[node];
}

// UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
//   if (node == nullptr) return nullptr;
//   queue<UndirectedGraphNode*> nodeQ;
//   nodeQ.push(node);
//   unordered_map<int, UndirectedGraphNode*> nodeMap;
//   nodeMap.emplace(node->label, new UndirectedGraphNode(node->label));
//   unordered_map<int, UndirectedGraphNode*>::iterator iter;
//   while (!nodeQ.empty()) {
//     UndirectedGraphNode *oriN   = nodeQ.front();
//     UndirectedGraphNode *cloneN = nodeMap.find(oriN->label)->second;
//     for (auto nb : oriN->neighbors) {
//       iter = nodeMap.find(nb->label);
//       if (iter == nodeMap.end()) {
//         nodeQ.push(nb);
//         UndirectedGraphNode* cloneNB = new UndirectedGraphNode(nb->label);
//         auto it = nodeMap.emplace(cloneNB->label, cloneNB);
//         iter = it.first;
//       }
//       cloneN->neighbors.push_back(iter->second);
//     }
//     nodeQ.pop();
//   }
//   return nodeMap.find(node->label)->second;
// }

int main() {
  return 0;
}
