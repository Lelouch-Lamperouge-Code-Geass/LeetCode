Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ? j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:
```
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.
```

# Solution

### Solution one

First of all, let's look at the naive solution. Preprocess to calculate the prefix sums S[i] = S(0, i), then S(i, j) = S[j] - S[i]. Note that here we define S(i, j) as the sum of range [i, j) where j exclusive and j > i. With these prefix sums, it is trivial to see that with O(n^2) time we can find all S(i, j) in the range [lower, upper].

```java
public int countRangeSum(int[] nums, int lower, int upper) {
    int n = nums.length;
    long[] sums = new long[n + 1];
    for (int i = 0; i < n; ++i)
        sums[i + 1] = sums[i] + nums[i];
    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (sums[j] - sums[i] >= lower && sums[j] - sums[i] <= upper)
                ans++;
    return ans;
}
```

Recall count smaller number after self where we encountered the problem

```
count[i] = count of nums[j] - nums[i] < 0 with j > i
```

Here, after we did the preprocess, we need to solve the problem

```
count[i] = count of a <= S[j] - S[i] <= b with j > i
ans = sum(count[:])
```

Therefore the two problems are almost the same. We can use the same technique used in that problem to solve this problem. One solution is merge sort based; another one is Balanced BST based. The time complexity are both O(n log n).

The merge sort based solution counts the answer while doing the merge. During the merge stage, we have already sorted the left half [start, mid) and right half [mid, end). We then iterate through the left half with index i. For each i, we need to find two indices k and j in the right half where

```
j is the first index satisfy sums[j] - sums[i] > upper and
k is the first index satisfy sums[k] - sums[i] >= lower.
```

Then the number of sums in [lower, upper] is j-k. We also use another index t to copy the elements satisfy sums[t] < sums[i] to a cache in order to complete the merge sort.

Despite the nested loops, the time complexity of the "merge & count" stage is still linear. Because the indices k, j, t will only increase but not decrease, each of them will only traversal the right half once at most. The total time complexity of this divide and conquer solution is then O(n log n).

One other concern is that the sums may overflow integer. So we use long instead.

```java
public int countRangeSum(int[] nums, int lower, int upper) {
    int n = nums.length;
    long[] sums = new long[n + 1];
    for (int i = 0; i < n; ++i)
        sums[i + 1] = sums[i] + nums[i];
    return countWhileMergeSort(sums, 0, n + 1, lower, upper);
}

private int countWhileMergeSort(long[] sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = countWhileMergeSort(sums, start, mid, lower, upper) 
              + countWhileMergeSort(sums, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    long[] cache = new long[end - start];
    for (int i = start, r = 0; i < mid; ++i, ++r) {
        while (k < end && sums[k] - sums[i] < lower) k++;
        while (j < end && sums[j] - sums[i] <= upper) j++;
        while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
        cache[r] = sums[i];
        count += j - k;
    }
    System.arraycopy(cache, 0, sums, start, t - start);
    return count;
}
```

C++ version, to be continue....

```cpp
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        const std::size_t n = nums.size();
        vector<long long> range_sum(n + 1, 0);
        for (std::size_t i = 0; i < n; ++i) {
            range_sum[i + 1] =  range_sum[i] + nums[i];
        }
        
        return countAndMerge(range_sum, lower, upper, 0, n + 1) ;
    }
private:
    void merge(vector<long long> &range_sum, 
               std::size_t begin,
               std::size_t mid,
               std::size_t end) {
        const std::size_t n = end - begin;
        vector<long long> cache(n, 0);
        std::size_t left(begin), right(mid);
        for (std::size_t i = 0; i < n; ++i) {
            if (right == end) {
                cache[i] = range_sum[left++];
            } else if (left == mid) {
                cache[i] = range_sum[right++];
            } else {
                if (right == end || range_sum[left] < range_sum[right]) {
                    cache[i] = range_sum[left++];
                } else {
                    cache[i] = range_sum[right++];
                }
            }
        }
        
        for (std::size_t i = 0; i < n; ++i) {
            range_sum[begin + i] = cache[i];
        }
    }
    std::size_t countAndMerge(vector<long long> &range_sum, 
                              int lower, 
                              int upper,
                              std::size_t begin, 
                              std::size_t end) {
        if (end <= begin + 1) {
            return 0;
        } else {
            std::size_t mid = begin + (end - begin) / 2;
            
            std::size_t count = countAndMerge(range_sum, lower, upper, begin, mid) 
                                + countAndMerge(range_sum, lower, upper, mid, end);
            std::size_t low(mid), up(mid);
            for (std::size_t i = begin; i < mid; ++i) {
                while (low < end && range_sum[low] - range_sum[i] < lower) {
                    ++ low;
                }
                
                while (up < end && range_sum[up] - range_sum[i] <= upper) {
                    ++ up;
                }
                
                count += up - low;
            }
            
            merge(range_sum, begin, mid, end);
            return count;
        }
    }
};
```

Using inplace_merge.

```cpp
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        const std::size_t n = nums.size();
        vector<long long> range_sum(n + 1, 0);
        for (std::size_t i = 0; i < n; ++i) {
            range_sum[i + 1] =  range_sum[i] + nums[i];
        }
        
        return countAndMerge(range_sum, lower, upper, 0, n + 1) ;
    }
private:
    std::size_t countAndMerge(vector<long long> &range_sum, 
                              int lower, 
                              int upper,
                              std::size_t begin, 
                              std::size_t end) {
        if (end <= begin + 1) {
            return 0;
        } else {
            std::size_t mid = begin + (end - begin) / 2;
            
            std::size_t count = countAndMerge(range_sum, lower, upper, begin, mid) 
                                + countAndMerge(range_sum, lower, upper, mid, end);
            std::size_t low(mid), up(mid);
            for (std::size_t i = begin; i < mid; ++i) {
                while (low < end && range_sum[low] - range_sum[i] < lower) {
                    ++ low;
                }
                
                while (up < end && range_sum[up] - range_sum[i] <= upper) {
                    ++ up;
                }
                
                count += up - low;
            }
            
            inplace_merge(range_sum.begin() + begin, range_sum.begin() + mid, range_sum.begin() + end);
            return count;
        }
    }
};
```

### Solution 3

__I believe it's only O(N^2), not O(NlogN), and thus not acceptable. If I'm not mistaken, multiset iterators are bidirectional iterators and distance takes linear time for them.__

The basic idea is to use a multiset to save sum, where sum at i = nums[0]+...+ nums[i]. At each i, only those sum[j] that satisfies lower=< sum[i]-sum[j]<= upper can generate a valid range[j,i]. so we only need to calculate how many j (0=< j< i) satisfy sum[i]-upper=< sum[j]<=-sum[i]-lower. The STL multiset can take care of sort and find upper_bound, lower_bound j. 

```cpp
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
          int res = 0;
            long long sum = 0;
            multiset<long long> sums;
            sums.insert(0);
            for (int i = 0; i < nums.size(); ++i) {
                sum += nums[i];
                res += distance(sums.lower_bound(sum - upper), sums.upper_bound(sum - lower));
                sums.insert(sum);
            }
            return res;
    }
};
```
