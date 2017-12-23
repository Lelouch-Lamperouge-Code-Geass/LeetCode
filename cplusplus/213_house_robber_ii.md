Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

 
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        std::size_t num_size(nums.size());
        if (num_size==1) return nums[0];
        return std::max( max_rob(nums,0,num_size-2) , max_rob(nums,1,num_size-1) );
    }
private:
    int max_rob(const vector<int> & nums,size_t start, size_t end) {
        int pre2(0),pre1(0);
        for (size_t i=start;i<=end;++i) {
            int cur_max = std::max(pre2+nums[i],pre1);
            pre2 = pre1;
            pre1 = cur_max; 
        }
        return pre1;
    }
};
```
