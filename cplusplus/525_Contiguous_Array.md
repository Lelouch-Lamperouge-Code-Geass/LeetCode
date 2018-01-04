Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

##### Example 1:

```
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
```

##### Example 2:

```
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
```

Note: The length of the given binary array will not exceed 50,000.

# Solution

The idea is to change 0 in the original array to -1. Thus, if we find SUM[i, j] == 0 then we know there are even number of -1 and 1 between index i and j. Also put the sum to index mapping to a HashMap to make search faster.

What if we have a sequence [0, 0, 0, 0, 1, 1]? the maximum length is 4, the count starting from 0, will equal -1, -2, -3, -4, -3, -2, and won’t go back to 0 again. But wait, the longest subarray with equal number of 0 and 1 started and ended when count equals -2. We can plot the changes of count on a graph, as shown below. Point (0,0) indicates the initial value of count is 0, so we count the sequence starting from index 1. The longest subarray is from index 2 to 6.

![alt](https://discuss.leetcode.com/assets/uploads/files/1487543036101-figure_1.png)

From above illustration, we can easily understand that two points with the same y-axis value indicates the sequence between these two points has equal number of 0 and 1.

Another example, sequence [0, 0, 1, 0, 0, 0, 1, 1], as shown below,

![alt](https://discuss.leetcode.com/assets/uploads/files/1487543760956-figure_2.png?v=qgb1lp804jg)

There are 3 points have the same y-axis value -2. So subarray from index 2 to 4 has equal number of 0 and 1, and subarray from index 4 to 8 has equal number of 0 and 1. We can add them up to form the longest subarray from index 2 to 8, so the maximum length of the subarray is 8 - 2 = 6.

Yet another example, sequence [0, 1, 1, 0, 1, 1, 1, 0], as shown below. The longest subarray has the y-axis value of 0.

![alt](https://discuss.leetcode.com/assets/uploads/files/1487544408978-figure_3.png)

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        for (int & num : nums) {
            if (num == 0) num = -1;
        }
        
        std::unordered_map<long long, int> mapper;
        mapper.insert(std::make_pair(0, -1));
        long long sum_so_far(0);
        std::size_t reval(0);
        for (std::size_t i = 0, n = nums.size(); i < n; ++i) {
            sum_so_far += nums[i];
            if (mapper.count(sum_so_far)) {
                reval = std::max(reval, i - mapper[sum_so_far]);
            } else {
                mapper.insert(std::make_pair(sum_so_far, i));
            }
        }
        
        return reval;
    }
};
```
