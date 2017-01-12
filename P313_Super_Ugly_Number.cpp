#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include"print.h"

using namespace std;

int nthSuperUglyNumber_2(int n, vector<int>& primes) {
  vector<int> uglyNums(1, 1); 
  vector<int> ptr_vec(primes.size(), 0);
  while (uglyNums.size() < n) {
    vector<int> candidates(primes);
    int minCandidate = numeric_limits<int>::max();
    for (int i = 0; i != primes.size(); ++i) {
      candidates[i] = uglyNums[ptr_vec[i]] * primes[i];
      if (candidates[i] < minCandidate) {
        minCandidate = candidates[i];
      }
    }
    for (int i = 0; i != primes.size(); ++i) {
      if (candidates[i] == minCandidate) {
        ++ptr_vec[i];
      }
    }
    uglyNums.push_back(minCandidate);
  }
  return uglyNums[n-1];
}

int nthSuperUglyNumber(int n, vector<int>& primes) {
  vector<int> uglyNums(1, 1); 
  vector<int> ptr_vec(primes.size(), 0);
  while (uglyNums.size() < n) {
    vector<int> candidates(primes);
    int minCandidate = numeric_limits<int>::max(), min_idx;
    int cp_num = uglyNums[uglyNums.size()-1];
    for (int i = 0; i != primes.size(); ++i) {
      while ( uglyNums[ptr_vec[i]] * primes[i] <= cp_num) {
        ++ptr_vec[i];
      }
      candidates[i] = uglyNums[ptr_vec[i]] * primes[i];
      if (candidates[i] < minCandidate) {
        minCandidate = candidates[i];
        min_idx = i;
      }
    }
    ++ptr_vec[min_idx];
    uglyNums.push_back(minCandidate);
  }
  return uglyNums[n-1];
}

int main() {
  vector<int> primes;
  primes.push_back(2);
  primes.push_back(3);
  primes.push_back(5);
  int i = 1600; 
  cout<<i<<"th Ugly Number is "<<nthSuperUglyNumber(i, primes)<<endl;
  cout<<i<<"th Ugly Number is "<<nthSuperUglyNumber_2(i, primes)<<endl;
  return 0;
}
