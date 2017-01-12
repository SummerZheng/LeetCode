#include<iostream>
#include<vector>
#include<math.h>
#include<limits>
#include<ctime>
#include"print.h"

using namespace std;

int countPrimes(int n) {
  if (n <= 2) return 0;
  vector<int> prime_vec(1, 2);
  for (int num = 3; num < n; ++num) {
    int nMax = sqrt(num), i;
    for (i = 0; prime_vec[i] <= nMax; ++i) {
      if (num % prime_vec[i] == 0)
        break;
    }
    if (prime_vec[i] > nMax) {
      prime_vec.push_back(num);
    }
  }
  return prime_vec.size();
} 

int countPrimes_sieve(int n) {
  if (n <= 2) return 0;
  int cp_num = sqrt(n) + 1;
  vector<bool> prime_vec(n, true);
  for (int i = 4; i < n ; i += 2 )
    prime_vec[i] = false;
  int prime_ct = 1; 
  for (int i = 3; i < n; i += 2) {
    if (prime_vec[i]) {
      ++prime_ct;
      if ( i < cp_num) {
        for (int j = i * i; j < n; j += 2 * i)
          prime_vec[j] = false;
      }
    }
  }
  return prime_ct;
}

int countPrimes_sieve_optimized(int n) {
  if (n <= 2) return 0;
  int prime_ct = 1, odds_num = n / 2; 
  int cp_num = sqrt(n) + 1, cp_ix = cp_num / 2;
  vector<bool> prime_vec(odds_num, true);
  for (int i = 1; i < odds_num; ++i) {
    if (prime_vec[i]) {
      ++prime_ct;
      if ( i < cp_ix ) {
        for (int j = 2 * i * (i + 1); j < odds_num; j += (2 *i + 1))
          prime_vec[j] = false;
      }
    }
  }
  return prime_ct;
}

int main() {
  for (int n = 1; n < 100000000; n *= 10) {
  // for (int n = 1; n < numeric_limits<int>::max(); n *= 10) {
    clock_t tbegin = clock();
    cout<<countPrimes(n)<<" primes smaller than "<<n;
    clock_t tend = clock();
    cout<<" in "<<double(tend - tbegin) / CLOCKS_PER_SEC<<" sec"<<endl;
    tbegin = clock();
    cout<<countPrimes_sieve(n)<<" primes smaller than "<<n;
    tend = clock();
    cout<<" in "<<double(tend - tbegin) / CLOCKS_PER_SEC<<" sec"<<endl;
    tbegin = clock();
    cout<<countPrimes_sieve_optimized(n)<<" primes smaller than "<<n;
    tend = clock();
    cout<<" in "<<double(tend - tbegin) / CLOCKS_PER_SEC<<" sec"<<endl;
  }
  return 0;
}
