Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

# Solution

```cpp
class Solution {
public:
    string get_range(int start, int end)
    {
        return start==end? to_string(start) : to_string(start)+"->"+to_string(end);
    }
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> result;
        int pre = lower-1;
        for(int i =0; i <= nums.size(); i++)
        {
           int cur = (i==nums.size()? upper+1:nums[i]);
           if(cur-pre >= 2) {
            result.push_back(get_range(pre+1,cur-1));
           }
           pre = cur;
        }
        return result;
    }
};
```
