Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.


# Solution
  

### Solution 1

We can maintain a ```k + 1``` size window to store the relevant numbers. Then the remain problem is how to check the absolute difference between numbers within this window. It's easier for us to make the numbers within this window arranges in ascending order, otherwise we need to compare the absolute difference one by one. We can use std::set, which is a red-black tree maintaining ascending order. 
  
```
|y - x| <= t <==> -t <= y - x <= t
```  
  
Basically, for a new number we are going to add into the window, we need to check whether there is a number x exists in this window to satisfy above condition.
  
```
|y - x| <= t <==> -t <= y - x <= t 

<==> x <= y + t  && x >= y - t 
```    

We can use set.lower_bound to find a range [x1....xn] to satisfy  ```x >= y - t ```, and then we just need to make sure at least one number in this range can satisfy ```x <= y + t```. Since x1 is the smallest number within this range, if it can't satisfy this requirement then none of the numbers in this range can meet our requirements.   
  
  
__We maintains a k size set, so the space complexity is O(k). And insert a number into the set cost O(log K) and so is lower_bound function, and if we use n to represents the total nubmers, the time compleixty is O(n * log k).__
  
```cpp  
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0) return false;
        // std::set is ordered automatically in ascending order
        std::set<long> window; // Use long to handle overflow
        for (std::size_t i = 0, n = nums.size(); i < n; ++i) {
            if (window.size() == k + 1) {
                window.erase(nums[i - k - 1]);
            }
            
            // Here we are trying to find a range [x1....xn]
            // which at least have one number x to satisfy
            // |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;
            
            // To satisfy x >= nums[i] - t, 
            // just need to make sure that x != window.end()
            auto x = window.lower_bound((long)nums[i] - t);
            
            // To satisfy x <= nums[i] + t.
            // Here x point to the smallest number within this range.
            if (x != window.end() && *x - (long)nums[i] <= t) {
                return true;
            }
            
            window.insert(nums[i]);
        }
        return false;
    }
};
```

### Solution 2


Since there is now a constraint on the range of the values of the elements to be considered duplicates, it reminds us of doing a range check which is implemented in tree data structure and would take O(LogN) if a balanced tree structure is used, or doing a bucket check which is constant time. We shall just discuss the idea using bucket here.

Bucketing means we map a range of values to the a bucket. For example, if t is 2 then the bucket size should be 3 and  0, 1, 2 should all map to the same bucket. However, 2 and 4 are a considered duplicates but does not map to the same bucket. This is fine since we are checking the buckets immediately before and after as well. So, as a rule of thumb, just make sure the size of the bucket is reasonable such that elements having the same bucket is immediately considered duplicates or duplicates must lie within adjacent buckets. 


Here each bucket at most should only store one value, if it tried to store two, then in ur previous check map.containsKey() already return true, and this is counted as duplicate. It doesn't even check bucket+1 or bucket-1 anymore.

I know u must concern the second map.put override the (bucket-1), puts a value which is further from (bucket), then it messed up the (bucket-1) check. But the thing is: if that is the case, u already tried to put two value into one bucket, which already terminates the program.

__We maintains a k size buckets, so the space complexity is O(k). And the time compleixty is O(n) since check/udpate bucket cost O(1).__

```cpp
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.empty() || t < 0) return false;
        
        int min_val = *std::min_element(nums.begin(), nums.end());
        
        // Each bucket should contains only one number.
        // If it contains two which means we already have a pair meets
        // the requirement, and should return true.
        std::unordered_map<long, long> buckets; // <bucket_id, value>
        const long bucket_size(t + 1);
        for (int i = 0, n = nums.size(); i < n; ++i) {
            if (buckets.size() == k + 1) {
                long remove_id = ((long)nums[i - k - 1] - (long)min_val) / bucket_size;
                buckets.erase(remove_id);
            }
            long bucket_id = ((long)nums[i] - min_val) / bucket_size;
            if (buckets.count(bucket_id)
               || buckets.count(bucket_id - 1) != 0 && std::abs(nums[i] - buckets[bucket_id - 1]) <= t
               || buckets.count(bucket_id + 1) != 0 && std::abs(nums[i] - buckets[bucket_id + 1]) <= t) {
                return true;
            }
            
            buckets[bucket_id] = nums[i];
        }
        
        return false;
    }
};
```
