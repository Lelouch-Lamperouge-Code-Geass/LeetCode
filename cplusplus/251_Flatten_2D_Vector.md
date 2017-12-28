Implement an iterator to flatten a 2d vector.

For example,
```
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]
``` 

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

* How many variables do you need to keep track?  
* Two variables is all you need. Try with x and y.  
* Beware of empty rows. It could be the first few rows.  
* To write correct code, think about the invariant to maintain. What is it?  
* The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?  
* Not sure? Think about how you would implement hasNext(). Which is more complex?  
* Common logic in two different places should be refactored into a common method.  

Follow up:  
* As an added challenge, try to code it using only iterators in C++ or iterators in Java.

# Solution

Note that both hasNext() and next() can be called many many times. In this case, we need to make sure that hasNext() don't move pointer forward, and next() should always move pointer forward.

Also check above hints for corner cases.

### Solution 1

```cpp
class Vector2D {
    vector<vector<int>>::iterator i, iEnd;
    int j = 0;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        i = vec2d.begin();
        iEnd = vec2d.end();
    }

    int next() {
        hasNext();
        return (*i)[j++];
    }

    bool hasNext() {
        while (i != iEnd && j == (*i).size())
            i++, j = 0;
        return i != iEnd;
    }
};
```

### Solution 2,  using only iterators in C++

```cpp
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        m_row_iter = vec2d.begin();
        m_row_end = vec2d.end();
        
        if (m_row_iter != m_row_end) {
            m_col_iter = m_row_iter->begin();
            m_col_end = m_row_iter->end();
        }
    }

    // We should modify pointers here, and this
    // method can be called multiple times.
    int next() {
        hasNext(); // Will not modify pointers unless it is necessary
        int reval = *m_col_iter;
        ++ m_col_iter;
        return reval;
    }
    
    // hasNext() should not change pointers unless it is necessary.
    // If current pointer is pointing the next value, we should not 
    // move it no matter how many times we call this method.
    bool hasNext() {
        // If current row have been all visited, we need to move 
        // to next row. While it is possible that next row is empty.
        while (m_col_iter == m_col_end 
               && m_row_iter != m_row_end) {
            ++ m_row_iter;
            
            // Need to check this row is empty or not.
            if (m_row_iter != m_row_end) {
                m_col_iter = m_row_iter->begin();
                m_col_end = m_row_iter->end();
            }
        }
        
        return m_col_iter != m_col_end;
    }
private:
    vector<vector<int>>::iterator m_row_iter, m_row_end;
    vector<int>::iterator m_col_iter, m_col_end;
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
```
