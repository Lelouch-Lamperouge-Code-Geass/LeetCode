Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
For example, given nums = [-2, 0, 1, 3], and target = 2.
Return 2. Because there are two triplets which sums are less than 2:

```
[-2, 0, 1]
[-2, 0, 3]
```

Follow up:  
Could you solve it in O(n^2) runtime?  

# Solution

The bruteforce solution is to exhaust all the possibilities, calculate the sum of all triplets and check whether the sum is smaller than target. The time complexity is O(N^3).

How can we do better?

Since the input array is "rambled", means it has no internal pattern that we can use to improve our algorithm, there are in general two methods we can do:

1. Use auxiliary data structure to help us, e.g. HashTable
2. Sort the input array and use the "sorted" pattern.

Here we will go with the second option.


We sort the array first. Then, for each element, we use the two pointer approach to find the number of triplets that meet the requirements. 

Let me illustrate how the two pointer technique works with an example:

```
target = 2

  i  lo    hi
[-2, 0, 1, 3]
```

We use a for loop (index i) to iterate through each element of the array. For each i, we create two pointers, lo and hi, where lo is initialized as the next element of i, and hi is initialized at the end of the array. 

Let triplet_sum = nums[i] + nums[lo] + nums[hi], and we compare triplet_sum to target and either decrease hi or increase lo. 

1. triplet_sum > target : We can't increase lo here because it only makes triplet_sum larger, therefore we can only decrease hi.    
2. triplet_sum == target : We can't increase lo here because it only makes triplet_sum larger, therefore we can only decrease hi.  
3. triplet_sum < target : Here it not only means we find one triplet, it also means that if we replace hi with any index within (lo,hi), the triplet_sum is still smaller than target. We just make ```reval += hi - lo``` and increase lo.  

##### Pitfall

1. The input array can be empty or smaller than 3.
2. The array can contain duplciates.

__Time complexity O(n ^ 2), space complexity O(1).__

```cpp
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.size() < 3) return 0;
        
        std::sort(nums.begin(), nums.end());
        
        int reval(0);
        for (std::size_t i = 0, n = nums.size(); i + 1< n; ++i) {
            std::size_t low(i + 1), high(n - 1);
            
            while (low < high) {
                int sum = nums[i] + nums[low] + nums[high];
                
                if (sum >= target) {
                    if(high > 0) -- high;
                } else { // sum < target
                    // We can replace hi with any index within (lo,hi) 
                    // and the triplet sum is still smaller than target 
                    reval += high - low;
                    ++ low;
                }
            }
        }
        
        return reval;
    }
};
```
