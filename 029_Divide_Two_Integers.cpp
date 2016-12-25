class Solution {
public:
  int divide(int dividend, int divisor) {
    if(dividend ==0 ) return 0;
    if(divisor == 0) return INT_MAX;
    int sign = dividend<0 ^ divisor<0 ? -1 : 1;
    long abs_d = std::labs(dividend), abs_s = std::labs(divisor);
    long reval(0);
    while(abs_d >= abs_s) {
      long count(1),val(abs_s);
      while ( (val<<1) <= abs_d ) {
        val <<= 1;
        count <<= 1;
      }
      reval += count;
      abs_d -= val;
    }
    reval *= sign;
    if(reval>INT_MAX || reval<INT_MIN) return INT_MAX;
    else return reval;
  }
};
