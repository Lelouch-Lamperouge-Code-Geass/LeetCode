class Queue {
public:
  // Push element x to the back of queue.
  void push(int x) {
    m_in_stack.push(x);
  }

  // Removes the element from in front of queue.
  void pop() {
    peek();
    m_out_stack.pop();
  }

  // Get the front element.
  int peek() {
    if ( m_out_stack.empty() ) {
      while (!m_in_stack.empty()) {
        m_out_stack.push(m_in_stack.top());
        m_in_stack.pop();
      }
    }
    return m_out_stack.top();
  }

  // Return whether the queue is empty.
  bool empty() {
    return m_in_stack.empty() && m_out_stack.empty();
  }
private:
  std::stack<int> m_in_stack;
  std::stack<int> m_out_stack;
};
