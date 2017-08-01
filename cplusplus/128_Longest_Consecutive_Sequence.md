Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

```cpp
/* Use hashmap to record number and its located interval's length.*/
class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    int max_len(0);
    // intervals stores the number and the length
    // of its located interval
    unordered_map<int,int> intervals;
    for (int num : nums) {
      if(intervals.find(num)!=intervals.end()) continue; // must required
      int begin = intervals.find(num-1) != intervals.end()?
        num - intervals[num-1] : num;
      int end = intervals.find(num+1) != intervals.end()?
        num + intervals[num+1] : num;
      int interval_length = end - begin + 1;
      intervals[begin] = intervals[end] = intervals[num] = interval_length;
      max_len = std::max(max_len,interval_length);
    }
    return max_len;
  }
};
```

```cpp
/* This solution looks like O(n^2) but it is actually O(n).
Let's say an input is [1,2,3,4,5], we will iterate the whole array when we check 1.
But for the rest numbers, the inner while is constant.*/
class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> my_set(nums.begin(),nums.end());
    int reval(0),end(0);
    for (int num : nums) {
      if(my_set.count(num-1)==0) {
        end =  num+1;//num is the begin of a range
        while (my_set.count(end)!=0) {
          ++ end;
        }
        reval = std::max(reval,end-num);//[num,end)
      }
    }
    return reval;
  }
};
```
