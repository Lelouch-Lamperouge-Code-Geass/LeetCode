class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    const std::size_t nums_size(nums.size());
    std::deque<int> deq;
    vector<int> reval;
    for(std::size_t i=0;i<nums_size;++i){
      if (!deq.empty() && deq.front() == i-k) deq.pop_front();
      while(!deq.empty() && nums[deq.back()] < nums[i]){
        deq.pop_back();
      }
      deq.push_back(i);
      if(i>=k-1) reval.push_back(nums[deq.front()]);
    }
    return reval;
  }
};
