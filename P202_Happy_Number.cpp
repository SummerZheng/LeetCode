#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int digit_square(int n) {
  int digit_square_sum = 0, cur_digit;
  while (n) {
    cur_digit = n % 10;
    n /= 10;
    digit_square_sum += cur_digit * cur_digit;
  }
  return digit_square_sum;
}

bool isHappy(int n) {
  unordered_set<int> myHash;
  while (!myHash.count(n)) {
    myHash.insert(n);
    n = digit_square(n);
  }
  return myHash.count(1)? true: false;
}

int main() {
  int a[] = {19, 1, 100, 0};
  vector<int> vec(a, end(a));
  for (int i = 0; i!= vec.size(); ++i) {
    cout<<vec[i]<<" is a Happy Number: "<<isHappy(vec[i])<<endl;
  }
  return 0;
}
