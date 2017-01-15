#include<iostream>

using namespace std;

int mySqrt(int x) {
  if (x == 1) return x;
  long long minRT = 0, maxRT = x, midRT, lastD = maxRT - minRT;
  do {
    lastD = maxRT - minRT;
    midRT = minRT + (maxRT - minRT) / 2;
    if (x < midRT * midRT) {
      maxRT = midRT;
    } else {
      minRT = midRT;
    }
  } while (maxRT - minRT < lastD); 
  return midRT; 
}

double mySqrt_BS(double x) {
  double minRT = 0, maxRT = x, midRT;
  double range = maxRT - minRT, tol = 1e-14;
  while (range > tol) {
    midRT = minRT + (maxRT - minRT) / 2;
    if (x < midRT * midRT) {
      maxRT = midRT;
    } else {
      minRT = midRT;
    }
    range = maxRT - minRT;
  }
  return midRT; 
}

double mySqrt_Newton(double x) {
  double rt = x, delta = x, tol = 1e-14;
  while (delta > tol) {
    delta = (rt * rt - x) / 2 / rt;
    rt = rt - delta;
  }
  return rt; 
}

int main() {
  cout<<mySqrt_Newton(0.1)<<endl;
  cout<<mySqrt_Newton(1.)<<endl;
  cout<<mySqrt_Newton(2.)<<endl;
  cout<<mySqrt_Newton(11.)<<endl;
  cout<<mySqrt_Newton(100.)<<endl;
  cout<<mySqrt_Newton(2147395599)<<endl;
  return 0;
}
