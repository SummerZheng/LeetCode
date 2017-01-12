#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string convertToTitle(int n) {
  string title = "";
  const int divisor = 26, base = static_cast<int>('A');
  int remainder; 
  while(n) {
    --n;
    remainder = n % divisor; 
    n /= divisor;
    title.push_back(static_cast<char>(base + remainder));
  }
  std::reverse(title.begin(), title.end());
  return title;
}

int titleToNumber(string s) {
  int num = 0;
  const int divisor = 26, base = static_cast<int>('A');
  int multiplier = 1, remainder;
  while (!s.empty()) {
    remainder = static_cast<int>(s.back()) - base + 1;
    num += multiplier * remainder; 
    multiplier *= divisor;
    s.pop_back();
  } 
  return num;
}

int main() {
  cout<<static_cast<int>('A')<<endl;
  cout<<static_cast<int>('Z')<<endl;
  cout<<static_cast<char>(66)<<endl;
  cout<<convertToTitle(28)<<endl;
  cout<<titleToNumber("AB")<<endl;
  return 0;
}
