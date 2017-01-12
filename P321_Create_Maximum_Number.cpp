#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// current space complexity O(M * N * k), with each DPmat ele the size of O(k)
// TLE, need to find a better way of DP
typedef vector<vector<vector<vector<int>>>> hashtype;
struct dHashPair{
  dHashPair(){}
  int maxDigit;
  vector<pair<int, int>> ixPairs;
};
typedef vector<vector<vector<dHashPair*>>> dHashtype;

int get_max_digit(const vector<vector<int> >& numsMat, const vector<int>& startIxes, int k, vector<pair<int, int> >& maxDigitIx, dHashtype& dHash) {
  if (dHash[startIxes[0]][startIxes[1]][k] == nullptr) {
    int skipD = numsMat[0].size() - startIxes[0] + numsMat[1].size() - startIxes[1] - k + 1;
    int maxDigit = -1;
    for (int vecIx = 0; vecIx != numsMat.size(); ++vecIx) {
      int skipD_copy = skipD, i = startIxes[vecIx];
      while (i != numsMat[vecIx].size() && skipD_copy) {
        if (numsMat[vecIx][i] >= maxDigit) {
          if (numsMat[vecIx][i] > maxDigit) {
            maxDigit = numsMat[vecIx][i];
            maxDigitIx.clear();
          }
          maxDigitIx.push_back(make_pair(vecIx, i));
        }
        ++i; --skipD_copy;
      }
    }
    dHashPair* ptr = new dHashPair;
    ptr->maxDigit = maxDigit;
    ptr->ixPairs = maxDigitIx;
    dHash[startIxes[0]][startIxes[1]][k] = ptr;
  }
  maxDigitIx = dHash[startIxes[0]][startIxes[1]][k]->ixPairs;
  return dHash[startIxes[0]][startIxes[1]][k]->maxDigit;
}

vector<int> maxNumber_util(vector<vector<int> >& numsMat, vector<int> startIxes, int k, hashtype& myHash, dHashtype& dHash) {
  if (k == 0) return vector<int>();
  // cout<<"try to access "<<startIxes[0]<<", "<<startIxes[1]<<", "<<k<<" of myHash"<<endl;
  if (myHash[startIxes[0]][startIxes[1]][k].empty()) {
    vector<pair<int, int>> maxDigitIx;
    int maxDigit = get_max_digit(numsMat, startIxes, k, maxDigitIx, dHash);
    vector<int> maxN = vector<int>(1, maxDigit);
    if (k-1) {
      vector<int> maxRight(k-1, 0);
      for (int i = 0; i != maxDigitIx.size(); ++i) {
        vector<int> newStartIxes(startIxes);
        newStartIxes[maxDigitIx[i].first] = maxDigitIx[i].second + 1;
        vector<int> temp = maxNumber_util(numsMat, newStartIxes, k-1, myHash, dHash);
        if (temp > maxRight)
          maxRight = temp;
      }
      maxN.insert(maxN.end(), maxRight.begin(), maxRight.end());
    }
    // cout<<"insert maxN into hash"<<endl;
    // print(maxN);
    myHash[startIxes[0]][startIxes[1]][k] = maxN;
  }
  return myHash[startIxes[0]][startIxes[1]][k];
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
  vector<vector<int> > numsMat;
  numsMat.push_back(nums1);
  numsMat.push_back(nums2);
  vector<int> startIxes(2, 0);
  hashtype myHash(nums1.size()+1, vector<vector<vector<int> > >(nums2.size()+1, vector<vector<int>>(k+1)));
  dHashtype dHash(nums1.size()+1, vector<vector<dHashPair*>>(nums2.size()+1, vector<dHashPair*>(k+1)));
  vector<int> maxN = maxNumber_util(numsMat, startIxes, k, myHash, dHash);
  return maxN;
}

int main() {
  int a[] = {3, 4, 6, 5};
  int b[] = {9, 1, 2, 5, 8, 3};
  int k = 5;
  // int a[] = {3, 9};
  // int b[] = {8, 9};
  // int k = 3;
  vector<int> nums1(a, end(a));
  vector<int> nums2(b, end(b));
  vector<int> maxNum = maxNumber(nums1, nums2, k);
  print(maxNum);
  return 0;
}
