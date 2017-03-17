class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    std::vector<int> mis; // monotonic increasing sequence
    for (int num : nums) {
      std::vector<int>::iterator lb = std::lower_bound(mis.begin(),mis.end(),num);
      if (lb == mis.end()) mis.push_back(num);
      else *lb = num;
    }
    return mis.size();
  }
};
