class Solution {
public:
  // The keypoint is how to make sure that we can halve n as many times as possible.
  // Put it in another way, we want to divede n by 2 as many times as possible.
  // Which means, if there is any chance that we can convert n to be multiple of 4,
  // we should do that without hesitation.
  // The only exception is number 3, since the only reason we convert n to be muptile of 4
  // is that we can "divide n by 4" in our recursion path.
  int integerReplacement(int n) {
    if (n==INT_MAX) return 32;
    // we know the input is always positive
    int count(0);
    while(n!=1) {
      if (n%2==0) {
        n /= 2;
      } else {
        if ( (n+1)%4==0 && n>4) {
          ++n;
        } else {
          --n;
        }
      }

      ++ count; // increase replacement count
    }
    return count;
  }
};
