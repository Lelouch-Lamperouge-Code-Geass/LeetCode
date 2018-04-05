Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
```
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, 
the order of elements returned by next should be: [1,1,2,1,1].
```

Example 2:
```
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, 
the order of elements returned by next should be: [1,4,6].
```


```cpp
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
 ```
 
# Knowledge
If you look at the definition of NestedInteger class, it treats individual objects and compositions uniformly, looks like it uses composite pattern.

The composite pattern describes a group of objects that is treated the same way as a single instance of the same type of object. The intent of a composite is to "compose" objects into tree structures to represent part-whole hierarchies. Implementing the composite pattern lets clients treat individual objects and compositions uniformly.
  
When dealing with Tree-structured data, programmers often have to discriminate between a leaf-node and a branch. This makes code more complex, and therefore, more error prone. The solution is an interface that allows treating complex and primitive objects uniformly. In object-oriented programming, a composite is an object designed as a composition of one-or-more similar objects, all exhibiting similar functionality. This is known as a "has-a" relationship between objects. The key concept is that you can manipulate a single instance of the object just as you would manipulate a group of them. The operations you can perform on all the composite objects often have a least common denominator relationship. For example, if defining a system to portray grouped shapes on a screen, it would be useful to define resizing a group of shapes to have the same effect (in some sense) as resizing a single shape.
  
Composite should be used when clients ignore the difference between compositions of objects and individual objects. If programmers find that they are using multiple objects in the same way, and often have nearly identical code to handle each of them, then composite is a good choice; it is less complex in this situation to treat primitives and composites as homogeneous.

# Solution

Edge cases:

```
[[]]
[[],[1].[[]],[2]]
```


### Solution one
Though this solution works, it copys the whole data.
In general an iterator shouldn't copy the entire data but just iterate over the original data structure.
  
```cpp
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
```

### Solution two

This solution is more reasonable since it doesn't clone the whole original input.
```cpp
class NestedIterator {
private:
    stack<vector<NestedInteger>::iterator> m_begins, m_ends;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        m_begins.push(nestedList.begin());
        m_ends.push(nestedList.end());
    }

    int next() {
        hasNext();
        int reval = m_begins.top()->getInteger();
        ++ m_begins.top(); // stack.top() return reference
        return reval;
    }

    bool hasNext() {
        while (!m_begins.empty()) {
            if (m_begins.top() == m_ends.top()) {
                m_begins.pop();
                m_ends.pop();
            } else {
                if (!m_begins.top()->isInteger()) {
                    auto  x = m_begins.top();
                    ++ m_begins.top();
                    m_begins.push(x->getList().begin());
                    m_ends.push(x->getList().end());
                } else {
                    return true;
                }
            }
        }
        
        return false;
    }
};
```

### Solution three

A good solution as well.

```cpp
class NestedIterator {
public:
    stack<NestedInteger> stk;
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; i--)
            stk.push(nestedList[i]);
    }       

    int next() {
        int val = stk.top().getInteger();
        stk.pop(); 
        return val;
    }       

    bool hasNext() {
        while (!stk.empty()) {
            NestedInteger curr = stk.top();
            if (curr.isInteger()) return true;
            stk.pop();
            for (int i = curr.getList().size() - 1; i >= 0; i--)
                stk.push((curr.getList())[i]);
        }           
        return false;
    }       
};
```

# An intersting observation

Below solution works and it is almost the same like above solution two.

Note here

```
vector<NestedInteger> &cur_list = m_begins.top()->getList();
```

If we remove the reference symbol `&`, it doesn't work. This is probably because ```m_begins.top()->getList();``` return a refence.

I still don't have an answer why this is hapenning, probably because the internal logic of ```&```. And I guess it depends on the compiler too.

```cpp
class NestedIterator {
private:
    stack<vector<NestedInteger>::iterator> m_begins, m_ends;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        m_begins.push(nestedList.begin());
        m_ends.push(nestedList.end());
    }

    int next() {
        hasNext();
        int reval = m_begins.top()->getInteger();
        ++ m_begins.top(); // stack.top() return reference
        return reval;
    }

    bool hasNext() {
        while (!m_begins.empty()) {
            if (m_begins.top() == m_ends.top()) {
                m_begins.pop();
                m_ends.pop();
            } else {
                if (!m_begins.top()->isInteger()) {
                    vector<NestedInteger> &cur_list = m_begins.top()->getList();
                    ++ m_begins.top();
                    m_begins.push(cur_list.begin());
                    m_ends.push(cur_list.end());
                } else {
                    return true;
                }
            }
        }
        
        return false;
    }
};
```
