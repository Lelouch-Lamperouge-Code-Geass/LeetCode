You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

# Solution

### Solution 1

If we know that the maximum amount of money we can rob ending with each house(a consecutive array ending with each house), then we know that the maximum amount of money we can rob tonight.

For each house, we have

```
max_rob[i] = std::max(nums[i] + max_rob[i - 2], max_rob[i - 1]);
```

Here, ```nums[i] + max_rob[i - 2]``` means we rob current house, and ```max_rob[i - 1]``` means we ignore current house.

Therefore, the solution is

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        std::size_t n = nums.size();
        std::vector<int> max_rob(n, 0);
        max_rob[0] = nums[0], max_rob[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            max_rob[i] = std::max(nums[i] + max_rob[i - 2], max_rob[i - 1]);
        }
        
        return max_rob.back();
    }
};
```

We can optimize the space complexity to be O(1).

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int pre2(0), pre1(0);
        for(std::size_t i = 0 ; i < nums.size(); ++i){
            int cur_max = std::max(pre1, pre2 + nums[i]);
            pre2 = pre1;
            pre1 = cur_max;
        }
        return std::max(pre2, pre1);
    }
};
```

### Solution 2

Basically the same idea as above solution, we use even and odd to record the maximum money of even/odd index house.

This is still a DP solution.

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int even = 0;
        int odd = 0;
    
        for (int i=0; i<nums.size(); i++)
        {
            if (i%2==0)
            {
                even = max(even+nums[i], odd);
            }
            else
            {
                odd = max(odd+nums[i],even);
            }
        }
    
        return max(even, odd);
    }
};
```
