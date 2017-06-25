class RandomizedSet {
public:
  /** Initialize your data structure here. */
  RandomizedSet() {

  }

  /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
  bool insert(int val) {
    if (m_value_index_pairs.find(val) != m_value_index_pairs.end()) {
      return false;
    } else {
      m_values.push_back(val);
      m_value_index_pairs[val] = m_values.size() - 1;
      return true;
    }
  }

  /** Removes a value from the set. Returns true if the set contained the specified element. */
  bool remove(int val) {
    if (m_value_index_pairs.find(val) == m_value_index_pairs.end()) {
      return false;
    } else {
      int last_value = m_values.back();
      m_value_index_pairs[last_value] = m_value_index_pairs[val];
      m_values[m_value_index_pairs[val]] = last_value;
      m_values.pop_back();
      m_value_index_pairs.erase(val);
      return true;
    }
  }

  /** Get a random element from the set. */
  int getRandom() {
    return m_values[rand() % m_values.size()];
  }
private:
  std::vector<int> m_values;
  std::unordered_map<int, std::size_t> m_value_index_pairs;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
