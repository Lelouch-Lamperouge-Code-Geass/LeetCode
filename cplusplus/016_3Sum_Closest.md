Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

```
  For example, given array S = {-1 2 1 -4}, and target = 1.

  The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```

# Solution

Similar to 3 Sum problem, use 3 pointers to point current element, next element and the last element. If the sum is less than target, it means we have to add a larger element so next element move to the next. If the sum is greater, it means we have to add a smaller element so last element move to the second last element. Keep doing this until the end. Each time compare the difference between sum and target, if it is less than minimum difference so far, then replace result with it, otherwise keep iterating.
  
The bruteforce solution is to exhaust all the possibilities, calculate the sum of all triplets and check whether the sum is smaller than target. The time complexity is O(N^3).

How can we do better?

Since the input array is "rambled", means it has no internal pattern that we can use to improve our algorithm, there are in general two methods we can do:

1. Use auxiliary data structure to help us, e.g. HashTable. Basically we will do a space-time tradeoff (A space-time or time-memory tradeoff in computer science is a case where an algorithm or program trades increased space usage with decreased time).
2. Sort the input array and use the "sorted" pattern.

Here we will go with the second option.

We sort the array first. Then, for each element, we use the two pointer approach to find the number of triplets that meet the requirements.

Sorting array takes O(NlogN), will our for loop with two pointers takes O(N^2).

__Time complexity : O(n^2)__

__Note: you need take care of duplicates carefully.__ 

```cpp
class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    if(nums.size()<=3) {
      return std::accumulate(nums.begin(), nums.end(), 0);
    }
    int reval(nums[0]+nums[1]+nums[2]);
    std::sort(nums.begin(),nums.end());
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      std::size_t low(i+1),high(nums_size-1);
      while (low<high) {
        int sum = nums[i]+nums[low]+nums[high];
        if (sum==target) {
          return target;
        }

        if (std::abs(sum-target)<std::abs(reval-target)) reval = sum;

        const int cur_high(nums[high]), cur_low(nums[low]);
        if (sum>target) {
          while(low<high && nums[high]==cur_high) -- high;
        } else {
          while(low<high && nums[low]==cur_low) ++ low;
        }
      }
      while (i+1<nums_size && nums[i+1]==nums[i]) ++i;
    }
    return reval;

  }
};
```
