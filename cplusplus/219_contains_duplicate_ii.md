
Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.


# Solution
    
We iterates over the array using a sliding window. The right of the window is at i, the left of the window is k steps back. The elements within that window are maintained using a hashset. While adding new element to the set, if the element already exists in the set, return true. If the control reaches out of for loop, it means that inner return true never executed, meaning no such duplicate element was found.    
    
```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // Keep k + 1 recent elements in this window
        std::unordered_set<int> window;
        for (std::size_t i = 0, n = nums.size(); i < n; ++i) {
            if (window.size() == k + 1) {
                // Erase leftmost element of the window
                window.erase(nums[i - k - 1]);
            }
            if (window.count(nums[i]) != 0) {
                return true;
            }
            window.insert(nums[i]);
        }
        return false;
    }
};
```
    
