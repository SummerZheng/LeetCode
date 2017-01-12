#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// counting sort O(N) for input in arbitrary order 
int hIndex_counting_sort(vector<int>& citations) {
  if (citations.empty()) return 0;
  cout<<"citation"<<endl;
  print(citations);
  int n = citations.size(), i;
  vector<int> ct_vec(n+1, 0);
  // marginal count
  for (i = 0; i != citations.size(); ++i) {
    int ix = citations[i] > n ? n : citations[i];
    ++ct_vec[ix]; 
  }
  cout<<"marginal"<<endl;
  print(ct_vec);
  // cumulative count
  for (i = n - 1; i >= 0; --i) {
    ct_vec[i] += ct_vec[i+1]; 
  }
  cout<<"cumulative"<<endl;
  print(ct_vec);
  for (i = n; i>=0 && ct_vec[i] < i; --i);
  return i;
}

// O(N) for input in ascending order 
int hIndex_linear(vector<int>& citations) {
  if (citations.empty()) return 0;
  int n = citations.size(), i;
  for (i = n-1; i>=0 && (n-i) <= citations[i]; --i);
  ++i;
  return min(n-i, citations[i]);
}


// Binary Search
// O(log(N)) for input in ascending order 
int hIndex_BS(vector<int>& citations) {
  print(citations); 
  if (citations.empty()) return 0;
  int n = citations.size(), pL = 0, pR = n-1, pM;
  if (n <= citations[0])  return n;     // (n-pL) <= citations[pL]
  if (1 > citations[n-1]) return 0;     // (n-pR) > citations[pR]
  while ( pL < pR - 1 ) {
    pM = (pL + pR) / 2;
    if ((n - pM) > citations[pM]) {
      pL = pM;
    } else if ((n - pM) <= citations[pM]) {
      pR = pM;
    }
  }
  ++pL;
  cout<<"pL is "<<pL<<endl;
  return min(n - pL, citations[pL]);
}

int hIndex(vector<int>& citations) {
  return hIndex_counting_sort(citations);
}

int main() {
  vector<int> vec;
  vec = vector<int>(1, 0);
  cout<<hIndex(vec)<<endl;
  vec.push_back(1);
  cout<<hIndex(vec)<<endl;
  vec = vector<int>(1, 1);
  cout<<hIndex(vec)<<endl;
  vec.push_back(1);
  cout<<hIndex(vec)<<endl;
  vec = vector<int>(1, 100);
  cout<<hIndex(vec)<<endl;
  vec.push_back(102);
  cout<<hIndex(vec)<<endl;
  
  int a[] = {0, 1, 3, 5, 6}; 
  vec = vector<int>(a, end(a));
  cout<<hIndex(vec)<<endl;
  int b[] = {0, 0, 4, 4}; 
  vec = vector<int>(b, end(b));
  cout<<hIndex(vec)<<endl;
  return 0;
}
