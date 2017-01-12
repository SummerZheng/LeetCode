#include<iostream>
#include<vector>

using namespace std;

int cal_ari_num(int n) {
  n -= 2;
  return n * (n+1)/2;
}

int numberOfArithmeticSlices(vector<int>& A) {
  if (A.size() <= 2) return 0;
  int cur_diff = A[1] - A[0];
  int cur_len = 2, numAriSeq = 0; 
  for (int i = 2; i != A.size(); ++i) {
    if (A[i] - A[i-1] == cur_diff) {
      ++cur_len;
    } else {
      numAriSeq += cal_ari_num(cur_len);
      cur_diff = A[i] - A[i-1];
      cur_len = 2;
    }
  }
  numAriSeq += cal_ari_num(cur_len) ;
  return numAriSeq;
}

int main() {
  int a[] = {2, 4, 6, 8, 10};
  vector<int> vec(a, end(a));
  cout<<numberOfArithmeticSlices(vec)<<endl;
  return 0;
}
