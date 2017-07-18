// Though this solution works, it copys the whole data.
// In general an iterator shouldn't copy the entire data but just iterate over the original data structure.
class NestedIterator {
public:
  NestedIterator(vector<NestedInteger> &nestedList) : m_pos(0) {
    for (const NestedInteger &nested_integer : nestedList) {
      ProcessNestedInteger(nested_integer);
    }
  }

  int next() {
    return m_numbers[m_pos++];
  }

  bool hasNext() {
    return m_pos < m_numbers.size();
  }
private:
  void ProcessNestedInteger(const NestedInteger &nested_integer) {
    if (nested_integer.isInteger()) {
      m_numbers.push_back(nested_integer.getInteger());
    } else {
      const vector<NestedInteger> &list = nested_integer.getList();
      for (const NestedInteger &list_item : list) {
        ProcessNestedInteger(list_item);
      }
    }
  }
  std::size_t m_pos;
  vector<int> m_numbers;
};

// This solution is more reasonable since it doesn't clone the whole original input.
class NestedIterator {
public:
  NestedIterator(vector<NestedInteger> &nestedList) {
    m_begins.push(nestedList.begin());
    m_ends.push(nestedList.end());
  }

  int next() {
    hasNext();
    return ( m_begins.top() ++ )->getInteger();
  }

  // Make sure this function won't move iterator forward,
  // so that even get called multiple times, items won't be lost.
  bool hasNext() {
    while (!m_begins.empty()) {
      if (m_begins.top() == m_ends.top()) {
        m_begins.pop();
        m_ends.pop();
      } else {
        auto x = m_begins.top();
        if (x->isInteger())
          return true;
        m_begins.top()++;
        m_begins.push(x->getList().begin());
        m_ends.push(x->getList().end());
      }
    }
    return false;
  }
private:
  stack<vector<NestedInteger>::iterator> m_begins, m_ends;

};
