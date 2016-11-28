/*1. there are no elements that appears more than n/3 times, then whatever the
  algorithm
   got from 1st round wound be rejected in the second round.
  2. there are only one elements that appears more than n/3 times, after 1st
  round one of
  the candicate must be that appears more than n/3 times(<2n/3 other elements
  could only
                                                         pair out for <n/3
  times), the other candicate is not necessarily be the second most frequent
                                                           but it would be
  rejected in 2nd round.
  3. there are two elments appears more than n/3 times, candicates would contain
  both of
  them. (<n/3 other elements couldn't pair out any of the majorities.) */
class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    const int nums_size(nums.size());
    // always keep two candidates here
    int val1(0), count1(0), val2(0), count2(0);
    for (int num : nums) {
      if (num == val1) {
        ++count1;
      } else if (num == val2) {
        ++count2;
      } else if (count1 == 0) {
        val1 = num;
        count1 = 1;
      } else if (count2 == 0) {
        val2 = num;
        count2 = 1;
      } else {
        --count1, --count2;
      }
    }

    vector<int> reval;
    if (std::count(nums.begin(), nums.end(), val1) * 3 > nums_size)
      reval.push_back(val1);
    if (val2 != val1 &&
        std::count(nums.begin(), nums.end(), val2) * 3 > nums_size)
      reval.push_back(val2);
    return reval;
  }
};
