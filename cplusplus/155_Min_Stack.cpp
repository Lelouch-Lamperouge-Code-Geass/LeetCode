/* 
Solution 1 
The most intuitive solution is storing number as well as minimal value as a pair
on each entry.
*/
class MinStack {
public:
  /** initialize your data structure here. */
  MinStack() {

  }

  void push(int x) {
    int min_val(x);
    if (!my_stack.empty() && my_stack.top().second<min_val) {
      min_val = my_stack.top().second;
    }
    my_stack.push(Pair(x,min_val));
  }

  void pop() {
    my_stack.pop();
  }

  int top() {
    return my_stack.top().first;
  }

  int getMin() {
    return my_stack.top().second;
  }
private:
  typedef std::pair<int,int> Pair;
  std::stack<Pair> my_stack;
};

/*
Solution 2 : using one extra space to store m_min.
The idea is to store the gap between the min value and the current value.
using long here to handle overflow.
 */
class MinStack {
public:

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
  if (m_stack.top()<0) {
    m_min -= m_stack.top();
  }
  m_stack.pop();
}

int top() {
  return  m_stack.top() <= 0 ? m_min : m_min+m_stack.top();
}

int getMin() {
  return m_min;
}
private:
long m_min;
std::stack<long> m_stack;
};
*/
