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

My personal version.

```cpp
class Vector2D {
public:
  Vector2D(std::vector<std::vector<int>> &vec2d) 
    : m_begin(vec2d.begin()), m_end(vec2d.end()), m_index(0){
    
  }
  int next() {
    hasNext();
    return (*m_begin)[m_index++];
  }
  bool hasNext() {
    while (m_index == m_begin->size() && m_begin != m_end) {
      ++ m_begin;
      m_index = 0;
    }
    return m_begin != m_end;
  }
private:
  std::size_t m_index;
  std::vector<std::vector<int>>::iterator m_begin, m_end;
};
void UnitTest() {
  vector<vector<int>> vec2d = {{1,2}, {3},{},{},{}, {4,5,6},{7}};
  Vector2D matrix(vec2d);
  while (matrix.hasNext()) {
    std::cout <<matrix.next() << std::endl;
  }
}

```
