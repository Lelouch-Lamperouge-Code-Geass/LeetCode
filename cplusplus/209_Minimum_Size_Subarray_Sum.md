Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.  

For example, given the array [2,3,1,2,4,3] and s = 7,  
the subarray [4,3] has the minimal length under the problem constraint.  

More practice:  
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

# Solution

### Solution one

If we know the minimal length of contiguous subarray ending with each index, then our final result will be the min value among all of them. Therefore, this problem  can be broken down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions. It is a dynamic programming problem.

In fact, this is a special dynamic programming problem, in general called "sliding-window problem".



We maintain a sliding window. For each index, we have a sliding window ending with this index.

1. If the ```window_sum``` is smaller than ```s```, it is either because we never have ```window_sum``` big enough to reach ```s```, or it is because previous we have such ```window_sum``` but we pop the ```window_start``` out (by shifting ```window_start``` to right). You may ask, why pop that ```window_start``` out? If we did not, for current index, don't we can have a window that makes ```window_sum``` larger or equals to ```s``` so that we can have a window meet requirement? The reason is that for any index we discarded from the sliding window, we have found the minimum window begin with that index, which will be definitely <= the window we can form right now. __In other words, when we discard the start index of the sliding window(by shifting window_start to right), the minimum window starting with that index have been found.__ 

For example, [...i...j...k...], if [i,j] can form a satisfied window, and we will pop i out of the sliding window after visited j(and we can say that we already find the minimum window begin with i). Even thourhg [i, k] can for a satisfied window too, but it will not be smaller than the window [i,j]. 

2. If the ```window_sum``` is larger than ```s```, the minimum window ending with current index have been found. Then we begin to discard the front elements of this sliding window until ```window_sum``` is smaller than ```s``` again. For each discarded indexes, the minimal window begin with it has been found.


__It is so important that I need to emphasize again. We can pop front index of the sliding window only because the minimum window begins with that index has been found, and there is no point to keep that index within sliding window.__

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
                // If such a upper bound can be find, that means
                // though the sum within range [p, i] is not less than s.
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
    // Return the first index i within [left, right],
    // which makes sums[i] > target.
    // If such index doesn't exist, return -1.
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

# Knowledge

### upper_bound and lower_bound in C++

* Iterator lower_bound (Iterator first, Iterator last, const val)
* Iterator upper_bound (Iterator first, Iterator last, const val)
 
lower_bound returns an iterator pointing to the first element in the range [first,last) which has a value not less than ‘val’.
 
upper_bound returns an iterator pointing to the first element in the range [first,last) which has a value greater than ‘val’.

```cpp
int main ()
{
    int gfg[] = {5,6,7,7,6,5,5,6};
     
    vector<int> v(gfg,gfg+8);    // 5 6 7 7 6 5 5 6
 
    sort (v.begin(), v.end());  // 5 5 5 6 6 6 7 7
 
    vector<int>::iterator lower,upper;
    lower = lower_bound (v.begin(), v.end(), 6); 
    upper = upper_bound (v.begin(), v.end(), 6); 
 
    cout << "lower_bound for 6 at position " << (lower- v.begin()) << '\n';
    cout << "upper_bound for 6 at position " << (upper - v.begin()) << '\n';
 
    return 0;
}
```

```
lower_bound for 6 at position 3
upper_bound for 6 at position 6
```

