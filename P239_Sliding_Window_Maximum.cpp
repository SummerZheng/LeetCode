#include<iostream>
#include<vector>
#include"print.h"
using namespace std;

// Amortized O(N), cause each ele enqueue/dequeue at most once

// Using a deque, Keep the max num at front
// Keep the later max candidates in descending order
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	deque<int> maxDQ;
	vector<int> slidingMax;
	for (int i = 0; i != nums.size(); ++i) {
		if (i >= k && nums[i-k] == maxDQ.front())
			maxDQ.pop_front();
		while (!maxDQ.empty() && nums[i] > maxDQ.back()) {
			maxDQ.pop_back();
		}
		maxDQ.push_back(nums[i]);
		if (i >= k-1) {
			slidingMax.push_back(maxDQ.front());
		}
	}
	return slidingMax;
}

// TODO: can also use two stacks to implement a queue
//       and borrow the max stack idea

int main() {
  vector<int> vec{1,3,-1,-3,5,3,6,7};
  print(maxSlidingWindow(vec, 3));
	return 0;
}
