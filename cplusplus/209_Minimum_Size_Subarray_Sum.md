Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.  

For example, given the array [2,3,1,2,4,3] and s = 7,  
the subarray [4,3] has the minimal length under the problem constraint.  

More practice:  
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

# Solution

### Solution one

__Time Complexity O(N), Space Complexity O(1)__

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        std::size_t start(0);
        int sum(0), min_len(INT_MAX);
        for (std::size_t i = 0, nums_size = nums.size();i < nums_size; ++i) {
            sum += nums[i];
            while (sum >= s) {
                min_len = std::min(min_len, (int)(i - start + 1));
                sum -= nums[start];
                ++ start;
            }
        }
        
        return min_len != INT_MAX ? min_len : 0;
    }
};
```

Well, you may wonder how can it be O(n) since it contains an inner while loop. Well, the key is that the while loop executes at most once for each starting position start. Then start is increased by 1 and the while loop moves to the next element. Thus the inner while loop runs at most O(n) times during the whole for loop from 0 to n - 1. Thus both the for loop and while loop has O(n) time complexity in total and the overall running time is O(n).

### Solution two

__Time Complexity O(NlogN), Space Complexity O(1)__

Now let's move on to the O(nlogn) solution. Well, this less efficient solution is far more difficult to come up with. The idea is to first maintain an array of accumulated summations of elements in nums. Specifically, for nums = [2, 3, 1, 2, 4, 3] in the problem statement, sums = [0, 2, 5, 6, 8, 12, 15]. Then for each element in sums, if it is not less than s, we search for the first element that is greater than sums[i] - s (in fact, this is just what the upper_bound function does) in sums using binary search.

Let's do an example. Suppose we reach 12 in sums, which is greater than s = 7. We then search for the first element in sums that is greater than sums[i] - s = 12 - 7 = 5 and we find 6. Then we know that the elements in nums that correspond to 6, 8, 12 sum to a number 12 - 5 = 7 which is not less than s = 7. Let's check for that: 6 in sums corresponds to 1 in nums, 8 in sums corresponds to 2 in nums, 12 in sums corresponds to 4 in nums. 1, 2, 4 sum to 7, which is 12 in sums minus 5 in sums.

We add a 0 in the first position of sums to account for cases like nums = [3], s = 3.

The code is as follows.

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        vector<int> sums = accumulate(nums);
        int n = nums.size(), minlen = INT_MAX;
        for (int i = 1; i <= n; i++) { 
            if (sums[i] >= s) {
                int p = upper_bound(sums, 0, i, sums[i] - s);
                if (p != -1) minlen = min(minlen, i - p + 1);
            }
        }
        return minlen == INT_MAX ? 0 : minlen;
    }
private:
    vector<int> accumulate(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n + 1, 0);
        for (int i = 1; i <= n; i++) 
            sums[i] = nums[i - 1] + sums[i - 1];
        return sums;
    }
    int upper_bound(vector<int>& sums, int left, int right, int target) {
        int l = left, r = right;
        while (l < r) {
            int m = l + ((r - l) >> 1);
            if (sums[m] <= target) l = m + 1;
            else r = m;
        }
        return sums[r] > target ? r : -1;
    }
};  
```
