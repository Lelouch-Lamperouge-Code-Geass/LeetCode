Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

```
Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
```

# Solution

```cpp
class Solution {
public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> reval;
    int low(0),high(numbers.size()-1);
    while(low<high){
      int sum(numbers[low]+numbers[high]);
      if(sum==target){
        reval.push_back(low+1);
        reval.push_back(high+1);
        return reval;
      } else if(sum>target){
        -- high;
      } else {
        ++ low;
      }
    }
    return reval;
  }
};
```
