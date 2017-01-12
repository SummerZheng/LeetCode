#include<iostream>
#include<vector>
#include<stack>

using namespace std;

// struct rectangle {
//   rectangle(int _ht = 0, int _wd = 0):ht(_ht), wd(_wd){}
//   int ht;
//   int wd;
// };
// 
// int largestRectangleArea(vector<int>& heights) {
//   stack<rectangle> myStack;
//   myStack.push(rectangle(-1, 1));
//   heights.push_back(0);
//   int maxA = 0, area;
//   for (int i = 0; i != heights.size(); ++i) {
//     rectangle topEle = myStack.top();
//     int combined_wd = 0;
//     while (topEle.ht >= heights[i]) {
//       combined_wd += topEle.wd;
//       if (topEle.ht * combined_wd > maxA)
//         maxA = topEle.ht * combined_wd;
//       myStack.pop();
//       topEle = myStack.top();
//     }
//     myStack.push(rectangle(heights[i], combined_wd + 1));
//   }
//   return maxA;
// }

inline int get_top_height(stack<int>& idxStack, vector<int>& heights) {
  return idxStack.empty() ? -1 : heights[idxStack.top()]; 
}

int largestRectangleArea(vector<int>& heights) {
  heights.push_back(0);
  stack<int> idxStack;
  int maxA = 0, topH, area_with_top;
  for (int i = 0; i != heights.size(); ++i) {
    topH = get_top_height(idxStack, heights); 
    while (topH >= heights[i]) {
      idxStack.pop();
      area_with_top = topH * (idxStack.empty() ? i : i - idxStack.top() - 1); 
      if (area_with_top > maxA)
        maxA = area_with_top;
      topH = get_top_height(idxStack, heights); 
    }
    idxStack.push(i);
  }
  return maxA;
}

int main() {
  // int a[] = {2, 1, 5, 6, 2, 3};
  // int a[] = {6, 2, 5, 4, 5, 1, 6};
  int a[] = {1, 1};
  vector<int> vec(a, end(a));
  cout<<largestRectangleArea(vec)<<endl;
  return 0;
}
