#include<iostream>
#include<vector>
#include<queue>
#include<deque>
//#include"print.h"

using namespace std;

typedef pair<int, int> myPair;

template <typename T>
void print(const deque<T>& dq) {
  for (auto iter = dq.begin(); iter != dq.end(); ++iter) {
    cout<<*iter<<" ";
  }
  cout<<endl;
}

inline myPair get_min(vector<deque<int> >& ugly_nums) {
  int curMin = std::numeric_limits<int>::max(), min_idx;
  for (int i = 0; i != ugly_nums.size(); ++i) {
    if (!ugly_nums[i].empty() && ugly_nums[i].front() < curMin) {
      curMin  = ugly_nums[i].front();
      min_idx = i;
    }
  }
  return make_pair(min_idx, curMin);
}

int nthUglyNumber_3(int n) {
  if (n == 1) return 1;
  --n;
  
  vector<int> prime_factors;
  prime_factors.push_back(2);
  prime_factors.push_back(3);
  prime_factors.push_back(5);
  
  vector<deque<int> > ugly_nums(prime_factors.size(), deque<int>());  
  for (int i = 0; i != prime_factors.size(); ++i) {
    ugly_nums[i].push_back(prime_factors[i]);
  }
  int cur_num, cur_idx, cp_num;
  while (n--) {
    myPair curMin = get_min(ugly_nums); 
    cur_num = curMin.second;
    cur_idx = curMin.first;
    cp_num  = ugly_nums[cur_idx].back(); 
    ugly_nums[cur_idx].pop_front();
    for (int i = 0; i != prime_factors.size(); ++i) {
      if (cur_num < std::numeric_limits<int>::max()/prime_factors[i] && cur_num > cp_num/prime_factors[i]) {
        ugly_nums[i].push_back(cur_num * prime_factors[i]);
      }
    }
    if(!n) {
      for (int i = 0; i != prime_factors.size(); ++i) {
        cout<<"queue "<<i<<endl;
        print(ugly_nums[i]);
      }
    }
  }
  return cur_num;
}


inline int get_curMin(const vector<queue<int> >& ugly_nums) {
  int curMin = std::numeric_limits<int>::max();
  for (int i = 0; i != ugly_nums.size(); ++i) {
    if (ugly_nums[i].front() < curMin)
      curMin = ugly_nums[i].front();
  }
  return curMin;
}

int nthUglyNumber_2(int n) {
  vector<int> prime_factors;
  prime_factors.push_back(2);
  prime_factors.push_back(3);
  prime_factors.push_back(5);
  vector<queue<int> > ugly_nums(prime_factors.size(), queue<int>());  
  for (int i = 0; i != prime_factors.size(); ++i) {
    ugly_nums[i].push(1);
  }
  int curMin = 1;
  while (n--) {
    curMin = get_curMin(ugly_nums);
    for (int i = 0; i != prime_factors.size(); ++i) {
      if (ugly_nums[i].front() == curMin)
        ugly_nums[i].pop();
      ugly_nums[i].push(curMin * prime_factors[i]);
    }
  }
  return curMin;
}

int nthUglyNumber_pq(int n) {
  vector<int> prime_factors;
  prime_factors.push_back(2);
  prime_factors.push_back(3);
  prime_factors.push_back(5);
  priority_queue<int, vector<int>, greater<int> >  pq_num;
  pq_num.push(1);
  int curMin = 1;
  while (n--) {
    curMin = pq_num.top();
    for (int i = 0; i != prime_factors.size(); ++i) {
      pq_num.push(curMin * prime_factors[i]);
    }
    //cout<<"cur top after round "<<n<<" is "<<pq_num.top()<<endl;
    while (pq_num.top() == curMin) {
      pq_num.pop();
    }
  }
  return curMin;
}

int main() {
//  for (int i = 1; i<= 2000; i += 10) {
//    cout<<i<<"th Ugly Number is "<<nthUglyNumber(i)<<endl;
//    cout<<i<<"th Ugly Number is "<<nthUglyNumber_3(i)<<endl;
//  }
//  cout<<std::numeric_limits<int>::max()<<endl;
  int i = 1600;
  cout<<i<<"th Ugly Number is "<<nthUglyNumber(i)<<endl;
  cout<<i<<"th Ugly Number is "<<nthUglyNumber_3(i)<<endl;
  return 0;
}
