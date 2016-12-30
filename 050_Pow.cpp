/*
Solution 1
*/

class Solution {
public:
  double myPow(double x, int n) {
    double ans = 1;
    unsigned long long p;
    if (n < 0) {
      p = -n;
      x = 1 / x;
    } else {
      p = n;
    }
    while (p) {
      if (p & 1)
        ans *= x;
      x *= x;
      p >>= 1;
    }
    return ans;
  }
};

/*
Solution 2
*/
class Solution {
public:
  double myPow(double x, int n) {
    if(n<0) return 1/x * myPow(1/x, -(n+1));
    if(n==0) return 1;
    if(n==2) return x*x;
    if(n%2==0) return myPow( myPow(x, n/2), 2);
    else return x*myPow( myPow(x, n/2), 2);
  }
};

/*
Solution 3
*/
class Solution {
public:
  double myPow(double x, int n) {
    if(n==0) return 1;
    double t = myPow(x,n/2);
    if(n%2) return n<0 ? 1/x*t*t : x*t*t;
    else return t*t;
  }
};
