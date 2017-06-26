// This algorithm's idea is:
// To iteratively determine what would be each bit of the final result from left to right.
// And it narrows down the candidate group iteration by iteration. e.g. assume input are a,b,c,d,...z, 26 integers in total.
// In first iteration, if you found that a, d, e, h, u differs on the MSB(most significant bit),
// so you are sure your final result's MSB is set. Now in second iteration, you try to see if among a, d, e, h, u there are
// at least two numbers make the 2nd MSB differs, if yes, then definitely, the 2nd MSB will be set in the final result.
// And maybe at this point the candidate group shinks from a,d,e,h,u to a, e, h.
// Implicitly, every iteration, you are narrowing down the candidate group, but you don't need to
// track how the group is shrinking, you only cares about the final result.
class Solution {
public:
  int findMaximumXOR(vector<int>& nums) {
    int max_val(0);
    int mask(0);
    for (int i = 31; i>=0; --i) {
      mask |= (1 << i);

      unordered_set<int> prefixes;
      for (int num : nums) {
        prefixes.insert(num & mask); // reserve Left bits and ignore Right bits
      }

      int target_next_max = max_val | (1 << i);

      for (int prefix : prefixes) {
        if (prefixes.count(target_next_max ^ prefix) != 0) {
          max_val = target_next_max;
          break;
        }
      }
    }

    return max_val;
  }
};
