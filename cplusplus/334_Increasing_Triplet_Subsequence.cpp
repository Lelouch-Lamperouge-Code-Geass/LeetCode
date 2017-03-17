/***
    Solution 1  : O(N)
 ***/

class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    int small(INT_MAX), big(INT_MAX);
    std::vector<int> sequence;
    for (int num : nums) {
      if (num <= small) { small = num; } // update small if num is smaller than both
      else if (num <= big) { big = num; } // update big only if greater than small but smaller than big
      else return true; // return if you find a number bigger than both
    }
    return false;
  }
};

/***
    Solution 2 : Longest Increasing Sequence, O(nlogn)
 ***/

class Solution {
public:
  bool increasingTriplet(vector<int>& nums) {
    std::vector<int> sequence;
    for (int num : nums) {
      auto iter = std::lower_bound(sequence.begin(), sequence.end(), num);
      if (iter == sequence.end()) {
        sequence.push_back(num);
      } else {
        *iter = num;
      }
      if (sequence.size() == 3) return true;
    }
    return false;
  }
};
