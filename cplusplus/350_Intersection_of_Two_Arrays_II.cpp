// Solution one, using HashMap
class Solution {
public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> reval;
    std::unordered_map<int, int> found;
    for (int num : nums1) {
      ++ found[num];
    }

    for (int num : nums2) {
      if (--found[num] >= 0) {
        reval.push_back(num);
      }
    }

    return reval;
  }
};


// Solution two, two pointers
class Solution {
public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> reval;
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());

    const std::size_t nums1_size(nums1.size()), nums2_size(nums2.size());
    std::size_t pos1(0), pos2(0);

    while (pos1 < nums1_size && pos2 < nums2_size) {
      if (nums1[pos1] == nums2[pos2]) {
        reval.push_back(nums1[pos1]);
        ++ pos1;
        ++ pos2;
      } else if (nums1[pos1] > nums2[pos2]) {
        ++ pos2;
      } else {
        ++ pos1;
      }
    }

    return reval;
  }
};
