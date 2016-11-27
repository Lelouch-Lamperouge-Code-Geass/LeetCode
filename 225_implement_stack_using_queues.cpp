class Stack {
public:
	// Push element x onto stack.
	void push(int x) {
		m_queue.push(x);
		const int n = m_queue.size()-1;
		for(int i=0;i<n;++i){
			m_queue.push(m_queue.front());
			m_queue.pop();
		}
	}

	// Removes the element on top of the stack.
	void pop() {
	    if(!m_queue.empty())
		    m_queue.pop();
	}

	// Get the top element.
	int top() {
		return m_queue.empty() ? INT_MIN :  m_queue.front();
	}

	// Return whether the stack is empty.
	bool empty() {
		return m_queue.empty();
	}
private:
    queue<int> m_queue;
};
