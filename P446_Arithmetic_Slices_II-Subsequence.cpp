#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include"print.h"

using namespace std;

int getSeqNum(long targetNum, long d, int lastIx, unordered_map<long, vector<int> >& idxHash, unordered_map<string, int>& DPmat, string key) {
  if (!DPmat.count(key)) {
    auto iter = idxHash.find(targetNum);
    int ct = 0, tempCt;
    bool flag = false;
    // cout<<"ori dp val for key "<<key<<" is "<<ct<<endl;
    if (iter != idxHash.end()) {
      for (auto pix = iter->second.rbegin(); pix != iter->second.rend() && *pix < lastIx; ++pix) {
        flag = true;
        string nextkey = to_string(*pix) + " " + to_string(d);
        tempCt = getSeqNum(targetNum - d, d, *pix, idxHash, DPmat, nextkey);
        ct += tempCt + 1;
      }
    }
    DPmat[key] = flag ? ct: -1;
    cout<<"updated dp val for key "<<key<<" is "<<ct<<endl;
  }
  return DPmat[key]; 
}

int numberOfArithmeticSlices(vector<int>& A) {
  if (A.size() <= 2) return 0;
  unordered_map<long, vector<int> > idxHash;
  for (int i = A.size()-1; i >= 0; --i) {
    idxHash[A[i]].push_back(i);
  }
  // use last_idx + diff as hash string key, and record the num of Arithmetic sequences
  unordered_map<string, int> DPmat;
  int numAriSeq = 0;
  long cur_diff, target_num;
  string key;
  for (int j = A.size()-1; j >= 2; --j) {
    unordered_set<string> tempHash;
    for (int i = j-1; i >= 1; --i) {
      cur_diff = static_cast<long>(A[j]) - A[i];
      key = to_string(j) + " " + to_string(cur_diff);
      if (!tempHash.count(key)) {
        tempHash.insert(key);
        int seq_num = getSeqNum(A[i], cur_diff, j, idxHash, DPmat, key);
        // cout<<"Arithmetic sequence ending at "<<A[j]<<" with difference "<<cur_diff<<" has num "<<seq_num<<endl;
        numAriSeq += seq_num > 0? seq_num: 0;  
      }
    }
  }
  return numAriSeq;
}

int main() {
  int a[] = {2, 4, 4, 6, 8, 10};
  // int a[] = {79,20,64,28,67,81,60,58,97,85,92,96,82,89,46,50,15,2,36,44,54,2,90,37,7,79,26,40,34,67,64,28,60,89,46,31,9,95,43,19,47,64,48,95,80,31,47,19,72,99,28,46,13,9,64,4,68,74,50,28,69,94,93,3,80,78,23,80,43,49,77,18,68,28,13,61,34,44,80,70,55,85,0,37,93,40,47,47,45,23,26,74,45,67,34,20,33,71,48,96};
  // int a[] = {-3444,-11196,9231,-4903,10811,-2268,9880,-9382,7575,-4337,937,1412,-1648,2626,3989,-943,3138,-8513,-5808,-4808,-1763,-4217,-4740,9867,2299,4089,-3134,-5835,2342,-4429,-2371,-9460,7044,-4648,10143,-2769,3985,4848,-6403,1731,2887,8693,9887,-10802,-5702,-8419,11142,4956,-3706,9932,4381,7391,-437,-1306,3570,-10739,9403,-1941,5938,-4975,-8415,-9476,10820,6028,-8928,7825,-7319,8650,7058,9413,10351,8277,-1758,2475,7688,-2845,-4116,8070,-3279,445,-9271,1428,-1672,-92,-11139,7820,7351,-8663,-5572,8153,-3280,10640,958,-4681,-5498,7733,-5348,10668,9191,-3456,-2427,8249,2524,-7146,4335,2751,-4013,4682,-9796,10071,-1098,1871,9046,-484,-6645,-6907,6502,9816,4891,-777,9856,-5173,-10504,-6075,8902,8578,4179,7865,10043,8921,-2117,4869,2546,8721,4751,-4359,2819,-6284,1726,3302,-8653,9678,353,-9211,8673,-7749,-551,-7476,-558,3804,2993,4541,-4397,9432,-1735,-3178,-9558,10279,4586,10661,2076,-3565,9934,4545,-4808,5195,6088,10215,-8006,-7778,-4584,-5905,-1556,3879,-3652,521,-10393,3446,2642,8529,3850,-1795,-9722,-3337,-3304,6632,-2460,-8928,-2456,7836,5562,115,-5106,2582,10815,-10794,-4081,-1413,5721,4605};
  vector<int> vec(a, end(a));
  print(vec);
  cout<<numberOfArithmeticSlices(vec)<<endl;
  return 0;
}
