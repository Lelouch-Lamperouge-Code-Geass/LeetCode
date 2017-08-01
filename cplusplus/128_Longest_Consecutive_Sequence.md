Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

# Solution

##### Solution one

We will use HashMap. The key thing is to keep track of the sequence length and store that in the boundary points of the sequence. For example, as a result, for sequence {1, 2, 3, 4, 5}, map.get(1) and map.get(5) should both return 5.

Whenever a new element n is inserted into the map, do two things:

* See if n - 1 and n + 1 exist in the map, and if so, it means there is an existing sequence next to n. Variables left and right will be the length of those two sequences, while 0 means there is no sequence and n will be the boundary point later. Store (left + right + 1) as the associated value to key n into the map.
* Use left and right to locate the other end of the sequences to the left and right of n respectively, and replace the value with the new length.

```cpp
/* Use hashmap to record number and its located interval's length.*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_map<int, int> interval_length;
        int reval(0);
        for (int num : nums) {
            if (interval_length[num] == 0) { // not visit before
                int left_len =  interval_length[num - 1];
                int right_len = interval_length[num + 1];
                
                int total_len = 1 + left_len + right_len;
                reval = std::max(reval, total_len);
                // Update this number and the interval's two ends
                // Note here left_len and right_len can be zero
                interval_length[num] = interval_length[num - left_len] 
                                     = interval_length[num + right_len]
                                    = total_len;
            }
        }
        
        return reval;
    }
};
```

##### Solution two

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
