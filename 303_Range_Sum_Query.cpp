/*
Since it says that the array won't change, and the sumRange will be called
many times, we need to optimize the calculation.
The idea is simple, for each entry in m_nums, it store the accumulate sum from 0 to that index.
Therefore, sum(i,j) = accu_sum(0,j) - accu_sum(0,i-1).
Be careful that when i==0, just return m_nums[j].
*/
class NumArray {
public:
  NumArray(vector<int> &nums) : m_nums(nums.size(),0) {
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      m_nums[i] = i==0? nums[i] : m_nums[i-1]+nums[i];
    }
  }

  int sumRange(int i, int j) {
    return i==0? m_nums[j] : m_nums[j] - m_nums[i-1];
  }
private:
  vector<int> m_nums;
};
