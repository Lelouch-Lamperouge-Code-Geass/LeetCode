class RandomizedCollection {
public:
  /** Initialize your data structure here. */
  RandomizedCollection() {

  }

  /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
  bool insert(int val) {
    bool not_contained(m_mapper.count(val) == 0);
    m_mapper[val].push_back(m_values.size());
    m_values.push_back(std::make_pair(val, m_mapper[val].size() - 1));
    return not_contained;
  }

  /** Removes a value from the collection. Returns true if the collection contained the specified element. */
  bool remove(int val) {
    bool is_contained(m_mapper.count(val) != 0);
    if (is_contained) {
      int last_val = m_values.back().first;
      int last_val_index = m_values.back().second;

      m_mapper[last_val][last_val_index] = m_mapper[val].back();
      m_values[ m_mapper[val].back() ] = std::make_pair(last_val, last_val_index);

      m_mapper[val].pop_back();
      if (m_mapper[val].empty()) {
        m_mapper.erase(val);
      }

      m_values.pop_back();
    }

    return is_contained;
  }

  /** Get a random element from the collection. */
  int getRandom() {
    return m_values[rand() % m_values.size()].first;
  }
private:
  std::unordered_map< int, std::vector<std::size_t> > m_mapper; // <value, vector of indices>
  std::vector< std::pair<int, std::size_t> > m_values; // <value, index in m_mapper[value] >
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
