#include<iostream>

using namespace std;

int trailingZeroes(int n) {
  int ct = 0;
  while(n) {
    n /= 5;
    ct += n;
  }
  return ct;
}

int main() {
  cout<<trailingZeroes(2)<<endl;
  cout<<trailingZeroes(5)<<endl;
  cout<<trailingZeroes(10)<<endl;
  cout<<trailingZeroes(15)<<endl;
  return 0;
}
