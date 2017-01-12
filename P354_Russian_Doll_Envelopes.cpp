#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include"print.h"

using namespace std;

// Method 1
// Build a Graph connecting env to all direct larger decendents
// Use DP to find max env according to max(children_max_env) + 1 
typedef pair<int, int> envelope;

static bool sort_by_w_then_h (envelope& e1, envelope& e2) { 
  if (e1.first != e2.first) {
    return e1.first < e2.first;
  } else {
    return e1.second < e2.second;
  }
}

struct gNode {
  gNode(int ix = -1, int _max = 0):idx(ix), maxEnv(_max), children(vector<gNode*>()){}
  int idx;
  int maxEnv;
  vector<gNode*> children;
};

struct graph {
  graph():root(new gNode()){}
  gNode* root; 
};

bool larger_than(int i1, int i2, vector<envelope>& envelopes) {
  if (i2 == -1) return true;
  if (envelopes[i1].first > envelopes[i2].first && envelopes[i1].second > envelopes[i2].second) {
    return true;
  } else {
    return false;
  }
}

void build_graph(gNode* p, int start_ix, vector<envelope>& envelopes, unordered_map<int, gNode*>& inGraph_hash) {
  for (int i = start_ix; i < envelopes.size(); ++i) {
    if (larger_than(i, p->idx, envelopes)) {
      if (!inGraph_hash.count(i)) {
        gNode* child = new gNode(i);
        inGraph_hash.emplace(i, child);
        build_graph(child, i+1, envelopes, inGraph_hash);
        p->children.push_back(child);
      } else {
        bool flag = false;
        for (auto iter = p->children.begin(); iter != p->children.end(); ++iter) {
          if (larger_than(i, (*iter)->idx, envelopes)) {
            flag = true; break;
          }
        }
        if (!flag) {
          gNode* node = inGraph_hash.find(i)->second;
          p->children.push_back(node);
        }
      }
    }
  }
}

int dp_getMax(gNode* p) {
  if (!p->maxEnv) {
    if (p->children.empty()) {
      p->maxEnv = 1;
    } else {
      int max_ct = 0, ct;
      for (auto iter = p->children.begin(); iter != p->children.end(); ++iter) {
        ct = dp_getMax(*iter);
        if (ct > max_ct) 
          max_ct = ct;
      }
      p->maxEnv = max_ct + 1;
    }
  }
  cout<<"max envelope for idx "<<p->idx<<" is "<<p->maxEnv<<endl;
  return p->maxEnv;
}

int maxEnvelopes_mytry(vector<pair<int, int>>& envelopes) {
  std::sort(envelopes.begin(), envelopes.end(), sort_by_w_then_h);
  print(envelopes);
  unordered_map<int, gNode*> inGraph_hash;
  graph myGraph;
  build_graph(myGraph.root, 0, envelopes, inGraph_hash);
  return dp_getMax(myGraph.root) - 1;
}

// Method 2
// DP method
int maxEnvelopes_DP(vector<pair<int, int>>& envelopes) {
  std::sort(envelopes.begin(), envelopes.end(), sort_by_w_then_h);
  vector<int> DPvec(envelopes.size(), 1);
  int max_num = DPvec.empty()? 0: 1, num;
  for (int i = DPvec.size()-2; i >= 0; --i) {
    for (int j = DPvec.size()-1; j >= i; --j) {
      if (larger_than(j, i, envelopes)) {
        DPvec[i] = max(DPvec[i], DPvec[j] + 1);
      }
    }
    if (DPvec[i] > max_num)
      max_num = DPvec[i];
  }
  return max_num; 
}

// Method 2
// ref to 300. Longest Increasing Subsequence O(NlogN) patience sorting method 
static bool cmp2(const envelope& e1, const envelope& e2) {
  if (e1.first != e2.first) {
    return e1.first < e2.first;
  } else {
    return e1.second > e2.second;
  }
}

static bool strictly_smaller(const envelope& e1, const envelope& e2) {
  if (e1.first < e2.first && e1.second < e2.second) {
    return true;
  } else {
    return false;
  }
}

int maxEnvelopes(vector<pair<int, int>>& envelopes) {
  if (envelopes.empty()) return 0;
  std::sort(envelopes.begin(), envelopes.end(), cmp2);
  vector<envelope> LISpile(1, envelopes[0]);
  for (int i = 1; i != envelopes.size(); ++i) {
    auto iter = std::lower_bound(LISpile.begin(), LISpile.end(), envelopes[i], strictly_smaller);
    if (iter == LISpile.end())
      LISpile.push_back(envelopes[i]);
    else
      *iter = envelopes[i];
  }
  return LISpile.size();
}

int main() {
  vector<pair<int, int> > envelopes;
  envelopes.push_back(make_pair(5, 4));
  envelopes.push_back(make_pair(6, 4));
  envelopes.push_back(make_pair(6, 7));
  envelopes.push_back(make_pair(2, 3));
  cout<<maxEnvelopes(envelopes)<<endl;  
  return 0;
}
