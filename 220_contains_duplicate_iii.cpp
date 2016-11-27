/* Solution 1*/
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if(nums.empty() || k < 1 || t < 0) return false;
    std::set<int> window;
    int min_val(INT_MAX), max_val(INT_MIN),nums_size(nums.size());
    for (int i=0;i<nums_size;++i) {
      if (window.size() == k+1) {
        window.erase(nums[i-k-1]);
      }
      auto iter = window.lower_bound(nums[i] - t);
      if (iter!=window.end() && *iter-nums[i]<=t) return true;
      window.insert(nums[i]);
    }
    return false;
  }
};

/* Solution 2*/
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if(nums.empty() || k < 1 || t < 0) return false;
    long min_val = * std::min_element(nums.begin(),nums.end());
    long bucket_size = t+1, nums_size(nums.size()); // t could be 0
    unordered_map<long,long> buckets; // <bucket_id,value>
    for (int i=0;i<nums_size;++i) {
      long bucket_id = (nums[i] - min_val) / bucket_size;
      if(buckets.size() > k) {
        long old_id = (nums[i-k-1] - min_val)/ bucket_size ;
        buckets.erase(old_id);
      }
      if ( buckets.count(bucket_id)
           || buckets.count(bucket_id-1) && std::abs(buckets[bucket_id-1] - nums[i]) <= t
           || buckets.count(bucket_id+1) && std::abs(buckets[bucket_id+1] - nums[i]) <= t
           ) return true;
      buckets[bucket_id] = nums[i];
    }
    return false;
  }
};
