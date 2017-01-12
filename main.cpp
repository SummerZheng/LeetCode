#include<iostream>
#include<string>
#include<bitset>
#include<vector>

using namespace std;

int getSum(int a, int b) {
  while (b) {
    int carry = a & b;
    a ^= b;
    b = carry << 1;
  }
  return a;
}


int main() {
  vector<int> ahaha(0);
  int a = 301, b = -167;
  cout<<getSum(a, b)<<endl;
  int *haha = new int(10);
  cout<<*haha<<endl;
  unsigned pos_num = -1;
  cout<<pos_num<<endl;
  int n = 137;
  cout<<"+n is ";
  bitset<31> num1(n);
  cout<<num1<<endl;
  cout<<"-n is ";
  bitset<31> num2(-n);
  cout<<num2<<endl;
  return 0;
}
