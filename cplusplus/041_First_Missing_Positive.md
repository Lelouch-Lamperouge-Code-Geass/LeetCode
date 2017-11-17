Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in __O(n) time__ and uses __constant space__.

# Solution

Let's ignore the time and space complexity first. How can we solve this problem?

One simple solution is to sort nums first, and then check from the first non-negative number. The time compleixty is O(NlogN) and space complexity is O(1).

Another simple solution is, since in best scenario nums will cover [1,n] so we just need a n+1 counter. If a positive number is present in nums, we set ```counter[number - 1] = true```. And finally we scan the counter and find the first entry whose value is false. In this case, time complexity is O(N) but the space complexity is O(N) too.

But wait, in this solution, if we can use the input vector as the counter then it is a O(N) time complexity O(1) space complexity solution! However, we can't use nums as a counter, instead we just __put every position number at their right position__!

For every positive number ```pos_num```, it should be put at index ```pos_num - 1```.

Therefore, we scan nums, and for every positive number, we check whether it is at the correct index or not. If it is not, try to swap it with the nunmber at the correct index because. 

There are below edge cases though:

1. The number at correct_index might be the same as nums[i], which means there are duplicates in nums. There is no point to swap them.  
2. After swap(nums[i], nums[correct_index]), don't move i forward yet! It's possible that the number just swapped to i-th entry is also a positive number which is not at the right position!  


```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        const int n(nums.size());
        std::size_t i(0);
        while (i < n) {
            int correct_index = nums[i] - 1;
            if (correct_index >= 0 
                && correct_index < n
                && correct_index != i
                && nums[correct_index] != nums[i]) {
                // Put the number at the correct index.
                std::swap(nums[correct_index], nums[i]);
                
                // Note that here we can't move forward yet.
                // It is highly possible that the number we just swapped into i-th position
                // also need to be mapped to the right position.
            } else {
                // Right now there are three cases:
                // 1. The nums[i] is either at the right position,
                // 2. nums[i] smaller than 1 or larger than n
                // 3. nums[i] are the same as nums[correct_index], it's meaningless to swap them
                ++ i;
            }
        }
        
        for (std::size_t i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1; 
            }
        }
        
        // The input array have [1,n]
        return n + 1;
    }
};
```
  
Different style.
    
```cpp
class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      while (nums[i]!=i+1
             && nums[i]-1>=0
             && nums[i]-1<nums_size
             && nums[i]!=nums[nums[i]-1]) {
        std::swap(nums[i],nums[nums[i]-1]);
      }
    }

    int index(0);
    while (index<nums_size) {
      if (nums[index]!= index+1) break;
      ++ index;
    }
    return index+1;
  }
};
```
