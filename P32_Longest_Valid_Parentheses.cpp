#include<iostream>
#include<string>
#include<stack>

using namespace std;

int longestValidParentheses(string s) {
  cout<<"string is "<<endl;
  cout<<s<<endl;
  // We use myStack to store the idx of '('
	stack<int> myStack;
  // minStart is the valid min start ix for the current paren chain
	int maxL = 0, minStart = 0, curIx, curStart;
	for (curIx = 0; curIx!= s.size(); ++curIx) {
		if (s[curIx] == '(') {
			myStack.push(curIx);
		} else {
      if (!myStack.empty()) { 
        myStack.pop();
        curStart = myStack.empty()? minStart : myStack.top()+1;
      } else {
        minStart = curIx+1; // invalidate the chain, reset minStart
        curStart = minStart;
      }
      maxL = max(maxL, curIx - curStart + 1);
      cout<<"curIx: "<<curIx;
      cout<<", minStart: "<<minStart;
      cout<<", maxL: "<<maxL<<endl;
    }
  }
  return maxL;
}

int main() {
  string s = "(()";
	cout<<longestValidParentheses(s)<<endl;
  s = ")()())";
	cout<<longestValidParentheses(s)<<endl;
  s = "(((()()))";
	cout<<longestValidParentheses(s)<<endl;
  s = "(((()()))())))()";
	cout<<longestValidParentheses(s)<<endl;
  s = "()(()";
	cout<<longestValidParentheses(s)<<endl;
  s = "()(())";
	cout<<longestValidParentheses(s)<<endl;
  s = ")(())(()()))(";
	cout<<longestValidParentheses(s)<<endl;
  s = ")(((((()())()()))()(()))(";
	cout<<longestValidParentheses(s)<<endl;
  return 0;
}
