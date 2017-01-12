#include<iostream>
#include<vector>

using namespace std;

template <typename T>
void print(const vector<T> &ivec){
    for (int i=0; i!=ivec.size(); ++i)
          cout<<ivec[i]<<" ";
      cout<<endl;
}

void rotate(vector<int>& nums, int k) {
  int n = nums.size();
  k %= n;
  if (k == 0) return;
  vector<int> part_right(nums.begin(), nums.begin() + n - k);
  print(part_right);
  for (int i = 0 ; i != nums.size(); ++i) {
    if (i < k)
      nums[i] = nums[i + n - k];
    else
      nums[i] = part_right[i-k];
  }
}

void rotate_from_ix(vector<int>& nums, int k, int initial_ix) {
  int n = nums.size();
  int ix_to_switch = initial_ix, num_to_switch = nums[initial_ix];
  int ix_switched, num_switched;
  do {
    ix_switched = (ix_to_switch + k) % n;
    num_switched = nums[ix_switched];
    nums[ix_switched] = num_to_switch;
    ix_to_switch = ix_switched;
    num_to_switch = num_switched;
  } while (ix_to_switch != initial_ix);
}

int get_gcd(int a, int b) {
  while(a%b) {
    a %= b; 
    swap(a, b);
  }
  return b;
}

void rotate_II(vector<int>& nums, int k) {
  int n = nums.size();
  k %= n;
  if (k == 0) return;
  int gcd = get_gcd(k, n);
  if ( gcd == 1 ) {
    rotate_from_ix(nums, k, 0);
  } else {
    for (int initial_ix = 0; initial_ix != gcd; ++initial_ix) {
      rotate_from_ix(nums, k, initial_ix);
    }
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5, 6};
  for (int i = 0; i != 7; ++ i) {
    vector<int> nums(a, end(a));
    rotate_II(nums, i);
    print(nums);
  }
  return 0;
}
