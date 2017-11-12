Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

##### Example 1:

```
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
```

##### Note:

* Then length of the input array is in range [1, 10,000].  
* The input array may contain duplicates, so ascending order here means <=.  

# Solution


### Naive solution by sorting

The original problem is asking for the shortest subarray that needs to be sorted in order to make the whole input array sorted. Assume nums is the input array with length n, nums_sorted is the sorted version of nums, nums[i, j](both indices inclusive) is such a subarray of the shortest length. Since we only need to sort nums[i, j] in order to transform nums into nums_sorted, all other elements in nums are left intact, which means the subarray nums[0, i - 1] will be exactly the same as subarray nums_sorted[0, i - 1], and the subarray nums[j + 1, n - 1] exactly the same as nums_sorted[j + 1, n - 1]. We can also conclude nums[i] != nums_sorted[i] and nums[j] != nums_sorted[j]. Otherwise the subarray nums[i, j] will not be the shortest (for example, if nums[i] == nums_sorted[i], sorting nums[i + 1, j] will also render nums sorted).

Therefore, the shortest subarray can be constructed as follows: its leftmost index can be obtained by finding the first index at which the two elements of nums and nums_sorted are different while its rightmost index can be obtained by finding the last such index.

The straightforward way for finding the two boundary indices would be comparing elements from nums and nums_sorted one by one. But we need to construct nums_sorted from nums first. This is the following __O(nlogn) time__ and __O(n) space__ solution:

```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::vector<int> sorted(nums);
        std::sort(sorted.begin(), sorted.end());
        
        std::size_t left(0), right(sorted.size() - 1);
        
        while (left <= right && sorted[left] == nums[left]) ++left; // first unmatch index 
        
        while (left <= right && sorted[right] == nums[right]) if (right > 0) --right; // last unmatch index 
        
        return right + 1 - left;
    }
};
```

### O(n) time two-pass solution

It turns out that the two boundary indices i and j can be found in linear time, if we take advantage of the following three properties:

1. nums[0, i - 1] and nums[j + 1, n - 1] are both sorted.

2. nums[i] != nums_sorted[i] and nums[j] != nums_sorted[j].

3. nums[i - 1] <= min and max <= nums[j + 1], where min and max are the minimum and maximum values of subarray nums[i, j].

The first and third properties guarantee that the subarray nums[0, i - 1] will be exactly the same as subarray nums_sorted[0, i - 1], and the subarray nums[j + 1, n - 1] exactly the same as nums_sorted[j + 1, n - 1], while the second property ensures that i will be the first index at which the two elements of nums and nums_sorted are different and j be the last such index.

Since we aim at the shortest subarrays, from the first property alone, we need to find the two longest sorted subarrays starting at index 0 and ending at index n - 1, respectively. Assume the two subarrays are nums[0, l] and nums[r, n - 1]. If there is overlapping between these two subarrays, i.e.l >= r, then the whole array is sorted so 0 will be returned. Otherwise, the input array is not sorted. However, we cannot say sorting nums[l, r] will leave the whole array sorted, because at this moment the third property may not be satisfied.

To guarantee the third property, assume min and max are the minimum and maximum values of subarray nums[l, r], then we need to decrease l as long as nums[l] > min, and increase r as long as nums[r] < max. After this is done, it can be shown that the second property will be met automatically, and nums[l + 1, r - 1] will be the shortest subarray we are looking for (that is, i = l + 1 and j = r - 1).

Finding the longest subarrays and the maximum and minimum values of the middle subarray takes one-pass. Ensuring the third property requires a second pass. Therefore we have this two-pass solution:

```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
            
        int left(0), right(nums.size() - 1);
        
        // Find the end index of the first non-decreasing subarray
        while (left < right && nums[left + 1] >= nums[left]) ++left;
        
        if (left == right) return 0;
        
        // Find the begin index of the last non-decreasing subarray
        while (left < right && nums[right - 1] <= nums[right]) --right;
        
        int min_val(INT_MAX), max_val(INT_MIN);
        // Here i need include left and right, e.g. [2,1]
        for (std::size_t i = left; i <= right; ++i) {
            min_val = std::min(min_val, nums[i]);
            max_val = std::max(max_val, nums[i]);
        }
        
        while (left >= 0 && nums[left] > min_val) -- left;
        while (right < nums.size() && nums[right] < max_val) ++ right;
        
        ++ left, -- right;
        return right + 1 - left;
    }
};
```
