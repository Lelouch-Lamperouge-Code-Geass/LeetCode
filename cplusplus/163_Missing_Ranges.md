Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

# Solution

Note that in the description "a sorted integer array where the range of elements are [lower, upper] inclusive",  itmade it clear that the elements will be between lower and upper.

Otherwise we need to handle when lower is larger than the smallest number or the upper is bigger than the biggest number in the array.

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

### Follow-up

What if lower can be larger than the smallest number or upper can be smaller than the biggest number in the array?

Simple, adjust the range first and then reuse above solution.

```cpp
std::string get_range(int start, int end){
  ostringstream oss;
  oss << start;
  if (start != end) oss << "->" << end;
  return oss.str();
}


vector<int> adjust_range(vector<int>& nums, int lower, int upper) {
  vector<int> reval;
  for (int num : nums) {
    if (num >= lower && num <= upper) {
      reval.emplace_back(num);
    }
  }
  return reval;
}

vector<string> findMissingRanges(vector<int>& numbers, int lower, int upper) {
  vector<string> reval;
  vector<int> nums = adjust_range(numbers, lower, upper);
  int pre = lower - 1;
  for (std::size_t i = 0, n = nums.size(); i <= n; ++ i) {
    int cur = i == n ? upper + 1: nums[i];
    
    if (cur != pre + 1) {
      reval.emplace_back( get_range(pre + 1, cur - 1));
    }
    pre = cur;
  }
  return reval;
}

void UnitTest() {
  vector<int> nums = {-5,1,3,50,75};
  vector<string> res = findMissingRanges(nums, -10, 70);
  for (string s : res) {
    std::cout << s << std::endl;
  }
}
```
