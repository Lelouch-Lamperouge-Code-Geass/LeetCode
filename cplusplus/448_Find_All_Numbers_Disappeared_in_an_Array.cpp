// Solution one
class Solution {
public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    std::vector<int> reval;
    const std::size_t n(nums.size());
    if (n != 0) {
      std::size_t index(0);
      while (index < n) {
        if (nums[index] != index + 1
            && nums[nums[index] - 1] != nums[index]) {
          std::swap(nums[index], nums[nums[index] - 1]);
        } else {
          ++ index;
        }
      }

      for (std::size_t i = 0; i < n; ++i) {
        if (nums[i] != i + 1) {
          reval.push_back(i + 1);
        }
      }
    }

    return reval;
  }
};

// Solution two
// The basic idea is that we iterate through the input array and mark elements as negative using
// nums[nums[i] -1] = -nums[nums[i]-1]
// In this way all the numbers that we have seen will be marked as negative.
// In the second iteration, if a value is not marked as negative, it implies we have
// never seen that index before, so just add it to the return list.
class Solution {
public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    std::vector<int> reval;
    const std::size_t n(nums.size());

    for (std::size_t i = 0; i < n; ++i) {
      // why std::abs ? nums[i] could have been changed to negative previously
      int index = std::abs(nums[i]) - 1;
      if (nums[index] > 0) {
        nums[index] = -  nums[index];
      }
    }

    for (std::size_t i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        reval.push_back(i + 1);
      }
    }

    return reval;
  }
};
