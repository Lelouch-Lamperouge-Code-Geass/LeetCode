// The intuitive solution to this problem is to split numbers into a smaller half and a bigger half.
// And then get number from smaller array and bigger array alternately。
// How can we do better to get O(1) space complexity?
// Then we have to perform the reconstruction in-place.
// We know that we can use partition algorithm to make an array with half smaller and half bigger.
// Here we can use three-way partitioning to arrange the numbers so that
// those larger than the median come first, then those equal to the median come next,
// and then those smaller than the median come last.
// We just need to twist it a little bit to make numbers wiggle.
// Make the partition results's indices [0, 1, 2, ... , n - 1, n] mapped to [1, 3, 5, ... , 0, 2, 4, ...].

class Solution {
public:
  void wiggleSort(vector<int>& nums) {
    std::size_t nums_size(nums.size());

    // Find median
    std::vector<int>::iterator median_pos = nums.begin() + nums_size / 2;
    std::nth_element(nums.begin(), median_pos, nums.end());
    int median = *median_pos;

    // Begin three way partition

    // [0,left) : numbers larger than median
    // [left, mid) : numbers equal to median
    // [mid, end] : numbers smaller than median
    std::size_t left(0), mid(0), right(nums_size - 1);

    // A functor to get wiggle index
    auto getWiggleIndex = [nums_size](int idx) { return (2 * idx + 1) % (nums_size | 1); };

    while (mid <= right) {
      const int cur_val = nums[getWiggleIndex(mid)];
      if (cur_val > median) {
        std::swap(nums[getWiggleIndex(mid)],
                  nums[getWiggleIndex(left)]); // swap the value to left
        ++ left;
        ++ mid;
      } else if (cur_val< median) {
        std::swap(nums[getWiggleIndex(mid)],
                  nums[getWiggleIndex(right)]); // swap the value to right
        -- right;
      } else { // cur_val == median
        ++ mid;
      }
    }
  }
};
