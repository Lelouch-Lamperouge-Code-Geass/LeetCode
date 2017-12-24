Note: This is an extension of [House Robber](https://leetcode.com/problems/house-robber/description/).

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

# Solution

When we try to solve a problem, a common technique we can use is "Pattern recognition", which means "Can you find a problem related to yours that has already been solved and use that to solve your problem?".

Luckily, we already solve a similar problem, "House Robber I", which the house is an acyclic array.

Then, it becomes how can we reduce this problem to the simpler one. Actually, extending from the logic that if house i is not robbed, then you are free to choose whether to rob house i + 1, you can break the circle by assuming a house is not robbed.

For example, 1 -> 2 -> 3 -> 1 becomes 2 -> 3 if 1 is not robbed.

Since every house is either robbed or not robbed and at least half of the houses are not robbed, the solution is simply the larger of two cases with consecutive houses, i.e. house i not robbed, break the circle, solve it, or house i + 1 not robbed. Hence, the following solution. I chose i = n and i + 1 = 0 for simpler coding. But, you can choose whichever two consecutive ones.
 
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        return std::max( robHouseInAcyclicArray(nums, 0, nums.size() - 2),
                         robHouseInAcyclicArray(nums, 1, nums.size() - 1));
    }
private:
    // We keep calculating the maximum profit when we reach each house.
    // The max value is based on
    // 1. Rob current house : pre2 + nums[i]
    // 2. Not rob current house : pre1
    // The return value is the maximum value of all the maximum profitx on
    // each house. Since all the numbers are positive, then it is the maximum
    // profit on the final house.
    int robHouseInAcyclicArray(vector<int> &nums,
                          std::size_t start,
                          std::size_t end) {
        int pre1(0), pre2(0);
        for (std::size_t i = start; i <= end; ++i) {
            int cur_max = std::max(pre2 + nums[i], pre1);
            pre2 = pre1, pre1 = cur_max;
        }
        return pre1;
    }
};
```
