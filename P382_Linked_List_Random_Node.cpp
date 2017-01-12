#include<iostream>
#include<random>
#include"print.h"

using namespace std;

/**
 * Definition for singly-linked list.
*/
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    /** @param head The linked list's head.
     *         Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* _head):head(_head), generator(default_random_engine()){
    }

    /** Returns a random node's value. */
    int getRandom() {
      int sp_val = head->val;
      ListNode *p = head;
      size_t i = 1;
      while (p) {
        std::uniform_int_distribution<int> distribution(1,i);
        int rand_num = distribution(generator);
        // cout<<"i is "<<i<<", and rand number is "<<rand_num<<endl;
        if (rand_num == 1)
          sp_val = p->val;
        p = p->next;
        ++i;
      }
      return sp_val;
    }

  private:
    ListNode *head;
    std::default_random_engine generator;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
**/

int main() {  
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  Solution solution(head);
  int N = 300000;
  vector<int> ct(3);
  for (int i = 0; i != N; ++i) {
    int val = solution.getRandom();
    ++ct[val-1];
  }
  print(ct);
  return 0;
}
