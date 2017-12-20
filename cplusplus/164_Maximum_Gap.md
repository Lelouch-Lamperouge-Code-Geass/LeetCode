Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

# Solution
  
Let's ignore the time/space complexity requirements first, how can we solve this problem in general?
  
We can just sort the array, and check the gap between neighbouring elements.  The time complexity will be O(NlogN), space complexity will be O(1).
  
Now，we have linear time/space complexity, which means we can perform Space-time tradeoff.
  
We have two common sorting algorithms to support linear time complexity.
  
1. Counting sort: A general counting sort is a bad idea. Because we have no idea what the minimum and maximum numbers can be. If their gap is big, we will ends up with a lot of empty entries. And the space complexity will be huge.
2. Radix sort:
3. Bucket sort:

In summary:

1. Counting sort -- simple buckets, simple processing, memory overhead
2. Radix sort -- simple buckets, sophisticated processing, speed overhead (and still need additional static memory)
3. Bucket sort -- sophisticated buckets, simple processing, requires dynamic memory, good in average

### Solution 1, bucket sort

We nedd to choose the bucket size wisely. Let's assume that we have one big bucket only, then that will not be helpful at all. 
  
Another example, we have ```1, 100, 101, 200```, and if we choose 100 as the bucket size then 1 and 100 will be in the first bucket, and 101 and 200 will be in the second bucket.  
  
Therefore, it will be good if different number can be put into different buckets. 
  
For people reading this, maybe this would help understanding how it works: basically we argue that the largest gap can not be smaller than (max-min)/(N-1), so if we make the buckets smaller than this number, any gaps within the same bucket is not the amount we are looking for, so we are safe to look only for the inter-bucket gaps.

So making the buckets smaller doesn't affect the correctness. for safety we might just as well use (max-min)/2N  

```cpp
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        
        const int min_val = *std::min_element(nums.begin(), nums.end());
        const int max_val = *std::max_element(nums.begin(), nums.end());
         
        const int num_of_buckets = nums.size();
        // max_val might equal min_val, therefore we add 1 here
        const int size_of_bucket = (max_val - min_val) / num_of_buckets + 1;
        std::vector<int> bucket_max_vals(num_of_buckets, INT_MIN);
        std::vector<int> bucket_min_vals(num_of_buckets, INT_MAX);
        for (int num : nums) {
            int bucket_index = (num - min_val) / size_of_bucket;
            bucket_max_vals[bucket_index] = std::max(bucket_max_vals[bucket_index], num);
            bucket_min_vals[bucket_index] = std::min(bucket_min_vals[bucket_index], num);
        }
        
        int max_gap(0), pre_max(min_val);
        for (int i = 0; i < num_of_buckets; ++i) {
            if (bucket_min_vals[i] == INT_MAX) {
                // Empty bucket
                continue;
            } else {
                int cur_gap = bucket_min_vals[i] - pre_max;
                max_gap = std::max(max_gap, cur_gap);
                pre_max = bucket_max_vals[i];
            }
        }
        
        return max_gap;
    }
};
```
