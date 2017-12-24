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

```cpp
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if (nums.empty() || k < 0 || t < 0) return false;
    int min_val = *std::min_element(nums.begin(),nums.end());
    unordered_map<long,long> buckets; // <bucket_id,value>
    const std::size_t nums_size(nums.size()),bucket_size(t+1);
    for (std::size_t i=0;i<nums_size;++i) {
      if (buckets.size()==k+1) {
        long old_id = (nums[i-k-1]-min_val) / bucket_size;
        buckets.erase(old_id);
      }
      long id = (nums[i]-min_val) / bucket_size;
      if (buckets.count(id)
          || buckets.count(id-1)!=0 && std::labs(nums[i]-buckets[id-1]) <=t
          || buckets.count(id+1)!=0 && std::labs(nums[i]-buckets[id+1]) <=t
          ) return true;
      buckets[id] = nums[i];
    }
    return false;
  }
};
```
