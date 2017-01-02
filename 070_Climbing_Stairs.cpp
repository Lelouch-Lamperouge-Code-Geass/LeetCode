class Solution {
public:
  int climbStairs(int n) {
    if (n<=2) return n;
    vector<int> ways_count(n+1,0);
    ways_count[1] = 1, ways_count[2] = 2;
    for (int i=3;i<=n;++i) {
      ways_count[i] = ways_count[i-2] + ways_count[i-1];
    }
    return ways_count[n];
  }
};

/*
We can optimize previous solution so that the space complexity is only O(1);
*/

class Solution {
public:
  int climbStairs(int n) {
    if (n<=2) return n;
    int two_steps_before = 1, one_step_before = 2;
    for (int i=3;i<=n;++i) {
      int cur = two_steps_before + one_step_before;
      two_steps_before = one_step_before;
      one_step_before = cur;
    }
    return one_step_before;
  }
};
