Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:

```
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
```

Examples:

```
Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
```

# Solution

We can break this problem into two smaller problems:

1. Given an array (A), number of cuts (CUTS), and the Largest sum of sub-arrays (MAX). Can you use at most CUTS cuts to segment array A into CUTS + 1 sub-arrays, such that the sum of each sub-array is smaller or equal to MAX?  
2. Given a lower bound (left), an upper bound (right), an unknown bool array (B), and an API uses i as input and tells you whether B[i] is true. If we know there exists an index k, that B[i] is false when i < k, and B[i] is true when i >= k. What is the fastest way to find this k (the lower bound)?  


__The time complexity is O(log(SumOfArray - MaxOfArray) * n).__

```cpp
class Solution {
private:
    // Given number of cuts allowable, and the maximum sum of subarray allowable，
    // return true if we can split the array with these two constraints.
    bool canSplit(const vector<int> &nums, 
                  const long long largest_subarray_sum, 
                  int num_of_cuts) {
        long long sum_of_cur_array(0);
        for (int num : nums) {
            if (num > largest_subarray_sum) return false;
            
            if (sum_of_cur_array + num <= largest_subarray_sum) {
                sum_of_cur_array += num;
            } else {
                sum_of_cur_array = num;
                -- num_of_cuts;
                if (num_of_cuts == 0) return false;
            }
        }
        
        return true;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        // Right is the largest possible sum of subarray.
        long long right = std::accumulate(nums.begin(), nums.end(), 0);
        // Left is the smallest possible sum of subarray.
        long long left = *(std::max_element(nums.begin(), nums.end()));
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (canSplit(nums, mid, m)) {
                right = mid; 
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};
```

My first solution.__Did not pass tests, TLE.__ The time complexity is way much worse than above solution.

```cpp
class Solution {
private:
    int splitArray(vector<int> & range_sum, int start, int end, int m) {
        if (m <= 1) return range_sum[end] - range_sum[start];
        
        int reval(INT_MAX);
        for (int i = start + 1; i < end; ++i) {
            int left_sum = range_sum[i] - range_sum[start];
            int right_sum = splitArray(range_sum, i, end, m - 1);
            reval = std::min(reval, std::max(left_sum, right_sum));
        }
        
        return reval;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        const int n(nums.size());
        vector<int> range_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            range_sum[i + 1] = range_sum[i] + nums[i];
        }
        
        return splitArray(range_sum, 0, n, m);
    }
};
```
