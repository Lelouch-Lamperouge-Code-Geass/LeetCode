class MinStack {
public:
  // The idea is to store the gap between the pre min value and the current value;
  MinStack() {

  }

  void push(int x) {
    if ( m_stack.empty() ) {
      m_stack.push(0);
      m_min = x;
    } else {
      m_stack.push(x - m_min);
      if( x<m_min ) m_min = x;
    }
  }

  void pop() {
    if(m_stack.top()<0){
      m_min = m_min - m_stack.top();
    }
    m_stack.pop();
  }

  int top() {
    return m_stack.top() > 0 ? m_min + m_stack.top() : m_min;
  }

  int getMin() {
    return m_min;
  }
private:
  long m_min;
  stack<long> m_stack;
};
