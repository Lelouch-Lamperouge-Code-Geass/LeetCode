class RandomizedSet {
private:
  std::vector<int> m_vec; // Store values
  std::unordered_map<int, std::size_t> m_mapper; // Store <value, vector index> pairs
public:
  /** Initialize your data structure here. */
  RandomizedSet() {

  }

  /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
  bool insert(int val) {
    bool reval(false);
    if (m_mapper.count(val) == 0) {
      reval = true;
      m_vec.push_back(val);
      m_mapper[val] = m_vec.size() - 1;
    }
    return reval;
  }

  /** Removes a value from the set. Returns true if the set contained the specified element. */
  bool remove(int val) {
    bool reval(false);

    if (m_mapper.count(val) != 0) {
      reval = true;
      // Put the last value into the to-be-deleted value's bucket.
      int last_val = m_vec.back();
      m_vec[m_mapper[val]] = last_val;
      m_mapper[last_val] = m_mapper[val];

      m_mapper.erase(val);
      m_vec.pop_back();
    }

    return reval;
  }

  /** Get a random element from the set. */
  int getRandom() {
    return m_vec[rand() % m_vec.size()];
  }

};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
