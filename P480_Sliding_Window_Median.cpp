#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include"print.h"

using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> med_sol;
        for (int i = 0; i != nums.size(); ++i) {
            cout<<"going to insert "<<nums[i]<<endl;
            if (i >= k) {
            cout<<"going to erase "<<nums[i-k]<<endl;
                if (nums[i-k] <= *minHalf.rbegin())
                    minHalf.erase(minHalf.find(nums[i-k]));
                else
                    maxHalf.erase(maxHalf.find(nums[i-k]));
                cout<<"balance after deletion"<<endl;
            }
            if (!minHalf.empty() && nums[i] < *minHalf.rbegin())
                minHalf.insert(nums[i]);
            else
                maxHalf.insert(nums[i]);
            cout<<"balance after insertion"<<endl;
            balanceSets();
            if (i >= k-1) med_sol.push_back(getMed());
        }
        return med_sol;
    }
    
private:
    double getMed() {
        // beware of precedence and overflow here
        return minHalf.size() > maxHalf.size() ? *minHalf.rbegin() : .5 * *minHalf.rbegin() + .5 * *maxHalf.begin();
    }
    void balanceSets() {
        cout<<"balence"<<endl;
        cout<<"minHalf size: "<<minHalf.size()<<endl;
        cout<<"maxHalf size: "<<maxHalf.size()<<endl;
        // be careful about c.size() which is unsigned
        // if rewrite as minHalf.size()-1 > maxHalf.size() is SERIOUSLY wrong is minHalf is empty!!!
        while (minHalf.size() > maxHalf.size() + 1) { 
            maxHalf.insert(*minHalf.rbegin());
            minHalf.erase(--minHalf.end()); // multiset, can only erase(iter) not erase(val), also cannot erase reverse_iter like rbegin()
        }
        while (maxHalf.size() > minHalf.size()) {
            minHalf.insert(*maxHalf.begin());
            maxHalf.erase(maxHalf.begin());
        }
        cout<<"The minHalf contains:"<<endl;
        for_each(minHalf.begin(), minHalf.end(), [] (int i) { cout<<i<<" "; });
        cout<<endl;
        cout<<"The maxHalf contains:"<<endl;
        for_each(maxHalf.begin(), maxHalf.end(), [] (int i) { cout<<i<<" "; });
        cout<<endl;
    }
    multiset<int> minHalf;
    multiset<int> maxHalf;
};


int main() {
  vector<int> vec{1,3,-1,-3,5,3,6,7};
  vec = {2147483647,1,2,3,4,5,6,7,2147483647};
  vec = {7,0,3,9,9,9,1,7,2,3};
  Solution sol;
  print(sol.medianSlidingWindow(vec, 6));
  return 0;
}
