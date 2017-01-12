#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct SLL {
  SLL():head(nullptr){}
  SLL(const vector<int> &vec):head(nullptr){
    for (int i = vec.size()-1; i>=0; --i) {
      insert(vec[i]);
    }
  }
  void print() {
    ListNode* cur = head;
    while (cur) {
      cout<<cur->val<<" ";
      cur = cur->next;
    }
    cout<<endl;
  }
  void removeElements(int ival){
    ListNode *cur = head, *prev = nullptr;
    while (cur) {
      if (cur->val != ival) {
        prev = cur;
      } else if (prev) {
        prev-> next = cur->next;  
      } else {
        head = cur->next;
      }
      cur = cur->next;
    }
  }
  private:
  void insert(int);
  ListNode* head;
};

void SLL::insert(int ele) {
  ListNode* newNode = new ListNode(ele);
  if (head) {
    newNode->next = head;
  }
  head = newNode;
}

//ListNode* removeElements(ListNode* head, int val) {
//}

int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> vec(a, end(a));
  SLL mylist(vec);
  mylist.print();
  mylist.removeElements(1);
  mylist.print();
  return 0;
}
