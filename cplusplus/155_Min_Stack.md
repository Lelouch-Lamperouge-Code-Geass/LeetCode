Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

* push(x) -- Push element x onto stack.
* pop() -- Removes the element on top of the stack.
* top() -- Get the top element.
* getMin() -- Retrieve the minimum element in the stack.

Example:

```
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
```

# Solution

##### Solution one



The most intuitive solution is storing number as well as minimal value as a pair on each entry.

  ```cpp
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
```

##### Solution two

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() : m_min(INT_MAX)  {
        
    }
    
    void push(int x) {
        if (x <= m_min) {
            // a new minimum value comes in,
            // push previous minimum value into stack
            // so that when pop up values, we can recover the previous minimum value
            // directly from stack
            m_values.push(m_min);
            m_min = x;
        }
        
        m_values.push(x);
    }
    
    void pop() {
        const int cur_val = m_values.top();
        if (cur_val == m_min) {
            // we are popping our minimal value now,
            // need recover previous minimal value 
            m_values.pop();
            m_min = m_values.top();
            m_values.pop();
        } else {
            m_values.pop();
        }
        
     
    }
    
    int top() {
        return m_values.top();
    }
    
    int getMin() {
        return m_min;
    }
private:
    int m_min;
    std::stack<int> m_values;
};
```


##### Solution three
Using one extra space to store m_min.
What the stack stores is the gap between current value and previous minimum value, it equals 

```current_value - previous_minimum_value```.

Therefore, when we call top(). There are two scenarios:
1. top() <= : which means current value is even smaller or at least equal to previous minimum value. So just return m_min.
2. top() is positive : which means current value is bigger than previous value, so return top() + m_min

When we call pop(), we just need to make sure update m_min when top() is negative.

Using long here to handle overflow.
  
```cpp
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
```
