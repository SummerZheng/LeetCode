#include<iostream>
#include<vector>
using namespace std;

void print(vector<int> &vec) {
  for (int i=0; i!= vec.size(); i++) {
    cout<<vec[i]<<" ";
  }
  cout<<endl;
}

class NumArray {
public:
    NumArray(vector<int> &nums): sum(vector<int>(nums.size()+1, 0)) {
      sum[0] = 0;
      for (int i=0; i!= nums.size(); i++) {
        sum[i+1] = sum[i] + nums[i];
      }
      print(nums);
      print(sum);
    }

    int sumRange(int i, int j) {
      return sum[j+1] - sum[i];
    }
private:
   vector<int> sum;   
};


int main(){
  int a[] = {-2, 0, 3, -5, 2, -1}; 
  vector<int> nums(a, end(a));
  NumArray numArray(nums);
  cout<<numArray.sumRange(0, 2)<<endl;
  cout<<numArray.sumRange(2, 5)<<endl;
  cout<<numArray.sumRange(0, 5)<<endl;
}
