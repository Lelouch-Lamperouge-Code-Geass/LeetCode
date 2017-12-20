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

### Solution 2, Radix sort

https://www.cs.usfca.edu/~galles/visualization/RadixSort.html


1. The first step is to find the maximum value in nums array, it will be the threshold to end while loop.  
2. Then use the radix sort algorithm to sort based on each digit from Least Significant Bit (LSB) to Most Significant Bit (MSB), that's exactly what's showing in the link.  
3. ```(nums[i] / exp) % 10``` is used to get the digit, for each digit, basically the digit itself serves as the index to access the count array. Count array stores the index to access aux array which stores the numbers after sorting based on the current digit.  
4. Finally, find the maximum gap from sorted array.  

Time and space complexities are both O(n). (Actually time is O(10n) at worst case for Integer.MAX\_VALUE 2147483647)

```cpp
class Solution {
private:
    void countingSort(vector<int> &nums, int exp) {
        // The base is 10, since 2147483647 only has 10 digits.
        int BASE(10);
        vector<int> counter(BASE, 0);
        
        // Store count of occurrences in counter
        for (int num : nums) {
            ++ counter[(num / exp) % 10];
        }
        
        // Change counter[i] so that counter[i] now contains actual
        //  position of this digit in output[]
        for (int i = 1; i < BASE; ++i) {
            counter[i] += counter[i - 1];
        }
        
        // Build the output array.
        // Will be overwritten anyway
        vector<int> output = nums;
        for (int i = nums.size(); i-- > 0;) {
            output[--counter[ (nums[i] / exp) % 10 ]] = nums[i];
        }
        
        nums = output;
    }
    
    void radixsort(vector<int>& nums) {
        // Find the maximum number to know number of digits
        const int max_val = *std::max_element(nums.begin(), nums.end());

        // Do counting sort for every digit. Note that instead
        // of passing digit number, exp is passed. exp is 10^i
        // where i is current digit number
        for (int exp = 1; max_val / exp > 0; exp *= 10) {
            countingSort(nums, exp);
        }
    }
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        vector<int> clone = nums;
        radixsort(clone);
        int max_gap(0);
        for (int i = 1, n = clone.size(); i < n; ++i) {
            max_gap = std::max(max_gap, clone[i] - clone[i - 1]);
        }
        return max_gap;
    }
};
```

# Knowledge

### Counting sort

In computer science, __counting sort__ is an algorithm for sorting a collection of objects _according to keys that are small integers_; that is, it is an integer sorting algorithm. It operates by counting the number of objects that have each distinct key value, and using arithmetic on those counts to determine the positions of each key value in the output sequence. Its running time is linear in the number of items and the difference between the maximum and minimum key values, so _it is only suitable for direct use in situations where the variation in keys is not significantly greater than the number of items_. However, __it is often used as a subroutine in another sorting algorithm, radix sort, that can handle larger keys more efficiently__.

In the most general case, the input to counting sort consists of a collection of n items, each of which has a non-negative integer key whose maximum value is at most k.

Because the algorithm uses only simple for loops, without recursion or subroutine calls, it is straightforward to analyze. The initialization of the count array, and the second for loop which performs a prefix sum on the count array, each iterate at most k + 1 times and therefore take O(k) time. The other two for loops, and the initialization of the output array, each take O(n) time. Therefore, the time for the whole algorithm is the sum of the times for these steps, O(n + k).

Because it uses arrays of length k + 1 and n, the total space usage of the algorithm is also O(n + k). For problem instances in which the maximum key value is significantly smaller than the number of items, counting sort can be highly space-efficient, as the only storage it uses other than its input and output arrays is the Count array which uses space O(k).

### Radix sort

In computer science, radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value. A positional notation is required, but because integers can represent strings of characters (e.g., names or dates) and specially formatted floating point numbers, radix sort is not limited to integers.

Most digital computers internally represent all of their data as electronic representations of binary numbers, so processing the digits of integer representations by groups of binary digit representations is most convenient. Two classifications of radix sorts are least significant digit (LSD) radix sorts and most significant digit (MSD) radix sorts. LSD radix sorts process the integer representations starting from the least digit and move towards the most significant digit. MSD radix sorts work the other way around.

### Bucket sort

Bucket sort, or bin sort, is a sorting algorithm that works by distributing the elements of an array into a number of buckets. Each bucket is then sorted individually, either using a different sorting algorithm, or by recursively applying the bucket sorting algorithm. It is a distribution sort, a generalization of pigeonhole sort, and is a cousin of radix sort in the most-to-least significant digit flavor. Bucket sort can be implemented with comparisons and therefore can also be considered a comparison sort algorithm. The computational complexity estimates involve the number of buckets.

Bucket sort works as follows:

1. Set up an array of initially empty "buckets".  
2. Scatter: Go over the original array, putting each object in its bucket.  
3. Sort each non-empty bucket.  
4. Gather: Visit the buckets in order and put all elements back into the original array.  


