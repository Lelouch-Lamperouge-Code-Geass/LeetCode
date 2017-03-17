class Solution {
public:
  int trailingZeroes(int n) {
    int result = 0;
    while(n){
      if(n/5) result += n/5;
      n /= 5;
    }
    return result;
  }
};
