#include<iostream>

using namespace std;
bool isPalindrome(int x) {
  if (x < 0) return false;
  int oriN = x, reverseN = 0;
  while (x && reverseN < oriN) {
    reverseN *= 10;
    reverseN += x%10;
    x /= 10;
  }
  return (oriN == reverseN)? true: false;
}

int main() {
  cout<<isPalindrome(1)<<endl;
  cout<<isPalindrome(11)<<endl;
  cout<<isPalindrome(121)<<endl;
  cout<<isPalindrome(1221)<<endl;
  cout<<isPalindrome(1231)<<endl;
  return 0;
}

