class Solution {
public:
  Solution(vector<int> nums) : m_nums(nums){

  }

  /** Resets the array to its original configuration and return it. */
  vector<int> reset() {
    return m_nums;
  }

  /** Returns a random shuffling of the array. */
  vector<int> shuffle() {
    std::vector<int> temp(m_nums);
    const std::size_t vec_size = m_nums.size();
    for (std::size_t i=0; i<vec_size; ++i) {
      std::size_t j = rand() % vec_size;
      std::swap(temp[i],temp[j]);
    }
    return temp;
  }
private:
  vector<int> m_nums;
};

