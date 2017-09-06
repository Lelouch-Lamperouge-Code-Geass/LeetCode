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

Note that since only the two ends of each interval get updated everytime, therefore the value in the middle may not have the updated new length.

The value in the middle is meaningless AFTER the left and right boundaries are added in the map. But this does not mean the middle value should not be included. Here is the explanation: although the boundaries and corresponding length to the other ends are maintained in the algorithm, we don't know whether it is LEFT or RIGHT by just looking at the single key-value pair. For example, a pair whose key = 10 and value = 3 can represent two possible intervals: [8, 10] or [10, 12]. Thanks to the middle values in the map, only one interval is possible by checking if map contains n, n-1 and n+1.

And also note that we should avoid checking the duplicate numbers.

Here is an example:

```
[1,2,0,1]

step 1 :   [1,1]
step 2 :   [1,2], [2,2,]
step 3 :   [0,3], [1,2], [2,3]
step 4 :    must skip checking number 1 again, otherwise we will get a length with 3 + 1 + 3 = 7.

```

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

An alternative solution, instead of storing length of interval, we can store the start and begin points of each interval.

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, pair<int, int>> mapper;
        int max_len(0);
        for (int num : nums) {
            if (mapper.count(num) == 0) {
                int begin = mapper.count(num - 1) > 0 ? mapper[num - 1].first : num;
                int end = mapper.count(num +1 ) > 0 ? mapper[num + 1].second : num;
                max_len = std::max(max_len, end + 1  - begin);
                mapper[num] = mapper[begin] = mapper[end] = make_pair(begin,end);
            }
        }
        return max_len;
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
