#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include<sstream>
#include<iomanip>
#include"print.h"

using namespace std;

vector<string> readBinaryWatch(int num) {
  const int max_h = 12, max_min = 60;
  const int h_digit = 4, m_digit = 6;
  vector<vector<string> > h_hash(h_digit+1);
  vector<vector<string> > m_hash(m_digit+1);
  for (int hour = 0; hour != max_h; ++hour) {
    bitset<h_digit> bit_hour(hour);
    h_hash[bit_hour.count()].push_back(to_string(hour));
  }
  for (int min = 0; min != max_min; ++ min) {
    bitset<m_digit> bit_min(min);
    std::ostringstream ss;
    ss<<std::setw(2)<<std::setfill('0')<<min;
    m_hash[bit_min.count()].push_back(ss.str());
  }
  vector<string> times;
  if (num < 0 || num > 10) return times;
  for (int i = 0; i <= h_digit && i <= num; ++i) {
    int j = num - i;
    cout<<i<<", "<<j<<endl;
    if (j > m_digit) continue;
    for (int ix1 = 0; ix1 != h_hash[i].size(); ++ix1) {
      for (int ix2 = 0; ix2 != m_hash[j].size(); ++ix2) {
        string str = h_hash[i][ix1] + ":" + m_hash[j][ix2]; 
        cout<<str<<endl;
        times.push_back(str);
      }
    } 
  }
  return times;
}

int main() {
  readBinaryWatch(1);
  return 0;
}
