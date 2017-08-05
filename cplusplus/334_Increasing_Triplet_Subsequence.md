Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:

```
Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
```

Your algorithm should run in O(n) time complexity and O(1) space complexity.

Examples:

```
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
```
    
# Solution

### Solution one

__time complexity is O(n), space complexity is O(1)__

```cpp
class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    int small(INT_MAX), big(INT_MAX);
    std::vector<int> sequence;
    for (int num : nums) {
      if (num <= small) { small = num; } // update small if num is smaller than both
      else if (num <= big) { big = num; } // update big only if greater than small but smaller than big
      else return true; // return if you find a number bigger than both
    }
    return false;
  }
};
```

### Solution 2 : Longest Increasing Sequence, O(nlogn)

This solution doesn't meet the requirement of time complexity and space complexity.
But it is still worth to check it out.
    
__time complexity is O(nlogn), space complexity is O(n)__

```cpp
class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    std::vector<int> sequence;
    for (int num : nums) {
      auto iter = std::lower_bound(sequence.begin(), sequence.end(), num);
      if (iter == sequence.end()) {
        sequence.push_back(num);
      } else {
        *iter = num;
      }
      if (sequence.size() == 3) return true;
    }
    return false;
  }
};
```
