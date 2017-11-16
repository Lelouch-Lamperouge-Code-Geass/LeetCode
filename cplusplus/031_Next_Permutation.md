Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
  
```
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
```

# Solution

Well, in fact the problem of next permutation has been studied long ago. From the [Wikipedia page](https://en.wikipedia.org/wiki/Permutation), in the 14th century, a man named Narayana Pandita gives the following classic and yet quite simple algorithm (with minor modifications in notations to fit the problem statement):

1. Begin with right side of the input vector, and goes backwards. Find the first index which makes nums[i] < nums[i + 1]. If no such index exists, then the input vector is sorted in NON-increasing order, just sort the vector and return.

2.  If such index exists, then nums{index + 1, end_index} is non-increasing, sort nums{index + 1, end_index} and make this range non-decreasing.

3. Find the smallest number in range nums{index + 1, end_index} which is larger than nums[index]. We can call std::upper_bound.

4. Swap nums[index] and nums[pos], here pos is the return value of std::upper_bound.


__Note__:
1. while (pos >= 1 && nums[pos - 1] >= nums[pos])
2. std::upper_bound

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.empty()) return;
        std::size_t pos(nums.size() - 1);
        const std::size_t MINUS_ONE(-1);
        
        // find first index backward which is smaller than its next neighbor,
        // and put pos at the next neightbor's position.
        while (pos >= 1 && nums[pos - 1] >= nums[pos]) {
            -- pos;
        }
        // Right now [pos,end] is a longest non-increasing sequence from right.
        // Let's reverse this interval.
        std::reverse(nums.begin() + pos, nums.end());
        
        if (pos == 0) return;
        
        
        -- pos;
        
        auto iter = std::upper_bound(nums.begin() + pos + 1, nums.end(), nums[pos]);
        
        std::swap(nums[pos], *iter);
    }
};
```

Different style.

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.empty()) return;
        
        const std::size_t n(nums.size());
        std::size_t i(n - 1);
        
        while (i - 1 < n && nums[i-1] >= nums[i]) --i;
        
        std::reverse(nums.begin() + i, nums.end());
        
        if (0 == i) return;
        
        int pivot(nums[i - 1]);
        
        std::size_t pos = std::upper_bound(nums.begin() + i, nums.end(), pivot) - nums.begin();
        std::swap(nums[i-1], nums[pos]);
    }
};
```
