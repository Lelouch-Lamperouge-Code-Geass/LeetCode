class Solution {
public:
  int majorityElement(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    const int n(nums.size());
    int cur_num(nums[0]), count(1);
    for (int i=1;i<n;++i) {
      if (nums[i]!=cur_num) {
        -- count;
        if (count==0) {
          cur_num = nums[i];
          count =1;
        }
      } else {
        ++ count;
      }
    }
    return cur_num;
  }
};
