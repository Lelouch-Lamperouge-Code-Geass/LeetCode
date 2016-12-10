/* Solution 1*/
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
  struct Data;
  Data* data;
public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);
  virtual ~Iterator();
  // Returns the next element in the iteration.
  int next();
  // Returns true if the iteration has more elements.
  bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums),m_peeked(false) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    if (!m_peeked) {
      m_peeked_val = Iterator::next();
      m_peeked = true;
    }
    return m_peeked_val;
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    int reval = m_peeked? m_peeked_val : Iterator::next();
    m_peeked = false;
    return reval;
  }

  bool hasNext() const {
    return m_peeked || Iterator::hasNext();
  }
private:
  bool m_peeked;
  int m_peeked_val;
};

/* Solution 2 The copy constructor here only takes constant time, only copies a pointer and an index */
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
  struct Data;
  Data* data;
public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);
  virtual ~Iterator();
  // Returns the next element in the iteration.
  int next();
  // Returns true if the iteration has more elements.
  bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.

  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    return Iterator(*this).next();
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    return Iterator::next();
  }

  bool hasNext() const {
    return Iterator::hasNext();
  }
};
