#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class MedianFinder {
  public:
    // default constructer is unnecessary here
    MedianFinder():maxHeap(priority_queue<int, std::vector<int>, std::less<int>>()),
                   minHeap(priority_queue<int, std::vector<int>, std::greater<int>>()) { }

    // Adds a number into the data structure.
    void addNum(int num) {
      if (maxHeap.size() == minHeap.size()) {
        if (!minHeap.empty() && num > minHeap.top()) {
          maxHeap.push(minHeap.top());
          minHeap.pop();
          minHeap.push(num);
        } else {
          maxHeap.push(num);
        }
      } else {
        if (maxHeap.top() <= num) {
          minHeap.push(num);
        } else {
          minHeap.push(maxHeap.top());
          maxHeap.pop();
          maxHeap.push(num);
        }
      }
    }

    // Returns the median of current data stream
    double findMedian() {
      cout<<"maxHeap contain "<<maxHeap.size()<<" ele with max ele "<<(maxHeap.size()? maxHeap.top(): INT_MIN)<<endl;
      cout<<"minHeap contain "<<minHeap.size()<<" ele with min ele "<<(minHeap.size()? minHeap.top(): INT_MAX)<<endl;
      if (maxHeap.size() == minHeap.size()) {
        return double(maxHeap.top() + minHeap.top()) / 2;
      } else {
        return maxHeap.top();
      }
    }

  private:
    // maxHeap will contain N or N+1 of the smaller half
    // minHeap will contain N of the larger half
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
int main() {
  MedianFinder mf;
  for (int i = -1; i != -6; --i) {
    cout<<"insert "<<i<<" into heap"<<endl;
    mf.addNum(i);
    cout<<mf.findMedian()<<endl;
  }
  return 0;
}

