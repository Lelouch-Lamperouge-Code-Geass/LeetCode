class Solution {
public:
  bool isPerfectSquare(int num) {
    if (num<0) return false;
    long low(0),high(num/2+1);
    while (low<=high) {
      long mid = low + (high-low)/2;
      long product = mid * mid;
      if (product == num) {
        return true;
      } else if (product > num) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return false;
  }
};
