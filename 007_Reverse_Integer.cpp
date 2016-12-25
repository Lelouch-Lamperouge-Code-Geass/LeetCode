class Solution {
public:
  int reverse(int x) {
    int sign = x>0 ? 1 : -1;
    x = std::abs(x);
    long res(0);
    while (x) {
      res = res * 10 + x % 10;
      x/=10;
    }
    res *= sign;
    return res>INT_MAX||res<INT_MIN? 0 : res;
  }
};
