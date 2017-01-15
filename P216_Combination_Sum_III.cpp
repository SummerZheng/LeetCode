#include<iostream>
#include<vector>
#include<unordered_map>
#include"print.h"
using namespace std;

const int sz = 9;

class Solution {
  public:
    vector<vector<int>> combinationSum3(int k, int n) {
      if (myHash.empty()) {
        vector<int> trail;
        create_dictionary(1, 9, 0, 0, trail);
      }
      string key = getKey(n, k); 
      return myHash[key];
    }
  private:
    void create_dictionary(int i, int j, int sum, int ct, vector<int>& trail) {
      if (i > j) {
        myHash[getKey(sum, ct)].push_back(trail);
      } else {
        create_dictionary(i+1, j, sum, ct, trail);
        sum += i;
        ++ct;
        trail.push_back(i);
        create_dictionary(i+1, j, sum, ct, trail);
        trail.pop_back();
      }
    }

    inline string getKey(int sum, int ct) {
      return to_string(sum) + "_" + to_string(ct);
    }
  public:
    static unordered_map<string, vector<vector<int>>> myHash;
};

unordered_map<string, vector<vector<int>>> Solution::myHash = unordered_map<string, vector<vector<int>>>();

int main() {
  Solution mySol;
  print(mySol.combinationSum3(2, 6));
  // print(mySol.combinationSum3(3, 7));
  // print(mySol.combinationSum3(3, 9));
  return 0;
}
