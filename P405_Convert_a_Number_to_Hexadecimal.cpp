#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string toHex(int num) {
  if (num == 0) return "0";
  char dict[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  const int base = 16, modN = base - 1;
  long n = num >= 0 ? num : 4294967296 + num;
  string str;
  while (n) {
    str.push_back(dict[n & modN]);
    n >>= 4;
    // str.push_back(dict[n%base]);
    // n /= base;
  }
  reverse(str.begin(), str.end());
  return str;
}

int main() {
  cout<<toHex(26)<<endl;
  cout<<toHex(-1)<<endl;
  return 0;
}
