#include<iostream>
#include<unordered_map>

using namespace std;

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

RandomListNode* get_clone_Node(unordered_map<RandomListNode*, RandomListNode*>& myHash, RandomListNode* pOri) {
  auto iter = myHash.find(pOri);
  if (iter == myHash.end()) {
    RandomListNode* cpN = new RandomListNode(pOri->label);
    iter = myHash.emplace(pOri, cpN).first;
  }
  return iter->second;
}

RandomListNode *copyRandomList(RandomListNode *head) {
  if (head==nullptr) return nullptr;
  unordered_map<RandomListNode*, RandomListNode*> myHash; // oriN, cpN
  RandomListNode *p = head;
  while (p) {
    RandomListNode *cloneN = get_clone_Node(myHash, p);
    if (p->next) {
      RandomListNode *cloneNext = get_clone_Node(myHash, p->next);
      cloneN->next = cloneNext;
    }
    if (p->random) {
      RandomListNode *cloneRandom = get_clone_Node(myHash, p->random);
      cloneN->random = cloneRandom;
    }
    p = p->next;
  }
  return myHash.find(head)->second; 
}

int main() {
  return 0;
}
