Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

# Solution

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> nodes;
        for(int i = 0;i<nums.size();i++)
        {
            if(nodes.find(nums[i])!=nodes.end())
                return true;
            nodes.insert(nums[i]);
        }
        return false;
    }
};
```
