Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

# Solution

Note that in the description "a sorted integer array where the range of elements are [lower, upper] inclusive",  itmade it clear that the elements will be between lower and upper.

Otherwise we need to handle when lower is larger than the smallest number or the upper is bigger than the biggest number in the array.

Other things we need to consider:

1. What about ```[2147483647], lower = -2147483648 upper = 2147483647``` ? Overflow is possible here.
2. The interval between lower and first number, and the interval between last number and upper. These two intervals are the most tricky part.


Here is my thought: 

1. For numbers within nums, we store previous number in pre, and check ```pre + 1 < cur\_number``` or not. If it is so, we should add range ```[pre + 1, cur\_number - 1]```.
2. One edge case is how to handle lower and the first number. We know that ```lower <= first number```, we can set ```pre = lower - 1```.
3. Another edge case is how to handle the last range, ```[last number, upper]```. We know that ```last number <= upper```, we need add the range if ```last number < upper```.

```cpp
class Solution {
private:
    std::string getRange(long from, long to) {
        return from == to ? std::to_string(from) : std::to_string(from) + "->" + std::to_string(to);
    }
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> reval;

        long pre((long)lower - 1);
        
        for (long num : nums) {
            if (pre + 1 < num) {
                reval.emplace_back(getRange(pre + 1, num - 1));
            }
            
            pre = num;
        }
        
        if (pre < upper) reval.emplace_back(getRange(pre + 1, upper));
        
        return reval;
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
