#include<iostream>

using namespace std;

int integerReplacement(int n) {
  long ln = static_cast<int>();
  if (n == 0) return 1;
  if (n == 1) return 0;
  if (n & 1) {
    return 1 + min(integerReplacement(n+1), integerReplacement(n-1));
  } else {
    int ct = 0;
    while (! (n & 1) ){
      n >>= 1;
      ++ct;
    }
    return ct + integerReplacement(n);
  }
}
int main() {
  cout<<integerReplacement(7)<<endl;
  cout<<integerReplacement(8)<<endl;
  return 0;
}
