Given an unsorted array of integers, find the length of longest __continuous__ increasing subsequence (subarray).

##### Example 1:

```
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
Even though [1,3,5,7] is also an increasing subsequence, 
    it's not a continuous one where 5 and 7 are separated by 4.
```

##### Example 2:

```
Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
```

__Note__: Length of the array will not exceed 10,000.

# Solution

Before we begin to solve this problem, let's recall what's subarray, subsequence, substring. Substring and subarray is in general continuous. But consecutivity is not implied for subsequence. Therefore, you need always ask for clarification from interviwer about consecutivity.

Now, let's solve this problem.

We need to find the __longest continuous increasing subsequence__, each word here is important because they defined the characteristics of this problem.

How can we find such a max length of the whole array? It turns out, if we know the length of longest continuous increasing subseqence __ending on each index__, the final results will be the maximum of them.

By thinking like this (using Auxiliary Problem), we can solve this problem by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, examine the solved subproblems and will combine their solutions to give the best solution for the given problem. This is what we call, "dynamic programming".

```
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int max_len_end_here(1), reval(1);
        for (int i = 1, n = nums.size(); i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                max_len_end_here += 1;
            } else {
                max_len_end_here = 1;
            }
            
            reval = std::max(reval, max_len_end_here);
        }
        
        return reval;
    }
};
```







