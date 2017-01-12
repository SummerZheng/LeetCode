#include<iostream>
#include<vector>
#include<random>
#include"print.h"

using namespace std;

class Solution {
  public:
    Solution(vector<int> _nums): nums(_nums), generator(default_random_engine()) { 
    }

    int pick(int target) {
      int dup_ct = 0, ix;
      for (int i = 0; i != nums.size(); ++i) {
        if (nums[i] == target) {
          ++dup_ct;
          std::uniform_int_distribution<int> distribution(1, dup_ct);
          int rand_ct = distribution(generator);
          if (rand_ct == 1)
            ix = i;
        }
      }
      return ix;
    }

  private:
    vector<int> nums;
    std::default_random_engine generator; 
};                    
                      
/**                   
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(nums);
* int param_1 = obj.pick(target);
*/


int main() {
  int a[] = {1,2,3,3,3};
  vector<int> vec(a, end(a));
  Solution solution(vec);
  int N = 1000;
  vector<int> ct_vec(5);
  for (int i = 0; i != N; ++i) {
    int j = solution.pick(3);
    ++ct_vec[j];
  }
  print(ct_vec);
  return 0;
}
