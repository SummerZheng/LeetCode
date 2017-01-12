#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>
using namespace std;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

inline bool is_prefix(const string& str1, const string& str2) {
  return str2.find(str1) == 0;
}

bool cp_significant_digit_greater(int i, int j) {
  string str_i = to_string(i), str_j = to_string(j);
  if ( is_prefix(str_i, str_j) || is_prefix(str_j, str_i)) {
    return str_i + str_j > str_j + str_i;
  }
  return str_i > str_j;
}

int rPartition(vector<int> &vec, int istart, int iend){
  int ix = rand()%(iend-istart+1)+istart;
  swap(vec[ix], vec[iend]);
  int key = vec[iend];
  int i, j;
  for(i=istart-1, j=istart; j!=iend; j++){
    //if(vec[j]<key)
    if (cp_significant_digit_greater(vec[j], key))
      swap(vec[++i], vec[j]);
  }
  swap(vec[++i], vec[iend]);
  return i;
}

void quickSort(vector<int> &vec, int istart, int iend){
  if(istart>=iend)
    return;
  int q = rPartition(vec, istart, iend);
  quickSort(vec, istart, q-1);
  quickSort(vec, q+1, iend);
}


string largestNumber(vector<int>& nums) {
  quickSort(nums, 0, nums.size()-1);
  print(nums);
  string largestNum;
  for (int i = 0; i != nums.size(); ++i) {
    largestNum.append(to_string(nums[i]));
  }
  if (largestNum[0] == '0') return "0";
  return largestNum;
}

int main() {
  int a[] = {3, 30, 34, 5, 9};
  vector<int> vec(a, end(a));
  cout<<largestNumber(vec)<<endl;
  return 0;
}
