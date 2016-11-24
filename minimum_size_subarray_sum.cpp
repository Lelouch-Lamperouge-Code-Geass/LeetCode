class Solution {
public:
  int minSubArrayLen(int s, vector<int>& nums) {
    int start(0), min_len(INT_MAX),n(nums.size()),sum(0);
    for (int i=0;i<n;++i) {
      sum += nums[i];
      while (sum>=s) {
        int cur_len = i - start + 1;
        min_len = std::min(min_len,cur_len);

        // shift start till sum < s
        sum -= nums[start];
        ++ start;
      }
    }
    return min_len==INT_MAX? 0 : min_len;
  }
};
