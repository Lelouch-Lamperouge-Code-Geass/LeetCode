class Solution {
public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_set<int> found(nums1.begin(),nums1.end());

    std::unordered_set<int> duplicate;
    for (int num: nums2) {
      if (found.count(num)!=0) {
        duplicate.insert(num);
      }
    }
    return std::vector<int>(duplicate.begin(),duplicate.end());
  }
};
