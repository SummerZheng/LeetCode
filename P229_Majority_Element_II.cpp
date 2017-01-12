#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

template <typename T>
void print(const T& t) {
  std::cout<<t<<std::endl;
}

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

inline int ct_ele(int ele, const vector<int>& vec) {
  int ct = 0;
  for (int i = 0; i != vec.size(); ++i) {
    if (vec[i] == ele)
      ++ct;
  }
  return ct;
}

inline int get_challenger_idx(const vector<int>& m_ct){
  int min_count = m_ct[0], min_idx = 0;
  for (int i = 1; i != m_ct.size(); ++i) {
    if (m_ct[i] < min_count) {
      min_count = m_ct[i];
      min_idx = i;
    }
  }
  return min_idx;
}

vector<int> majorityElement_II(std::vector<int>& nums) {
  if (nums.empty()) return vector<int>();
  const int max_sz = 3;
  vector<int> m_ele, m_ct;
  for (int i = 0; i != nums.size(); ++i) {
    bool challenger = true;
    for (int ix = 0; ix != m_ele.size(); ++ix) {
      if (nums[i] == m_ele[ix]) {
        ++m_ct[ix];
        challenger = false;
      }
    }
    if (challenger) {
      if (m_ele.size() < max_sz) {
        m_ele.push_back(nums[i]);
        m_ct.push_back(1);
      } else {
        int challenger_ix = get_challenger_idx(m_ct);
        if ( m_ct[challenger_ix] == 1) {
          m_ele[challenger_ix] = nums[i];
        } else {
          --m_ct[challenger_ix];
        }
      }
    }
  }
  print(m_ele);
  print(m_ct);
  vector<int> verified_m_ele;
  for (int i = 0; i != m_ele.size(); ++i) {
    int ct = ct_ele(m_ele[i], nums);
    if (ct > nums.size() / 3)
      verified_m_ele.push_back(m_ele[i]);
  }
  return verified_m_ele;
}


int main() {
  int a[] = {2,2,9,3,9,3,9,3,9,3,9,3,9,3,9,3,9};
  std::vector<int> vec(a, std::end(a));
  print(majorityElement_II(vec));
  return 0;
}
