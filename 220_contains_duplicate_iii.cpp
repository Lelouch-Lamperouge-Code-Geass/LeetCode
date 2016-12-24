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
