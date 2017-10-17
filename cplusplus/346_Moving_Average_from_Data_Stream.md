Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

For example,

```
MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
```

# Solution


```cpp
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) : m_size(size), m_sum(0) {
        
    }
    
    double next(int val) {
        m_queue.push(val);
        m_sum += val;
        
        if (m_queue.size() > m_size) {
            m_sum -= m_queue.front();
            m_queue.pop();
        }
        
        return m_sum / m_queue.size();
    }
private:
    double m_sum;
    int m_size;
    queue<int> m_queue;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
```
