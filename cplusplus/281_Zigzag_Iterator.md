Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:
```
v1 = [1, 2]
v2 = [3, 4, 5, 6]
```
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question – Update (2015-09-18):
The “Zigzag” order is not clearly defined and is ambiguous for k > 2 cases. If “Zigzag” does not look right to you, replace “Zigzag” with “Cyclic”. For example, given the following input:

```
[1,2,3]
[4,5,6,7]
[8,9]
```
It should return [1,4,8,2,5,9,3,6,7].

# Solution

Uses a linkedlist to store the iterators in different vectors. Every time we call next(), we pop an element from the list, and re-add it to the end to cycle through the lists.

####  Use queue

```cpp

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (v1.size() != 0)
            Q.push(make_pair(v1.begin(), v1.end()));
        if (v2.size() != 0)
            Q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        vector<int>::iterator it = Q.front().first;
        vector<int>::iterator endIt = Q.front().second;
        Q.pop();
        if (it + 1 != endIt)
            Q.push(make_pair(it+1, endIt));
        return *it;
    }

    bool hasNext() {
        return !Q.empty();
    }
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> Q;
};

```

####  Use list

```cpp
class ZigzagIterator {
private:
    typedef vector<int>::iterator VecIter;
    list<pair<VecIter, VecIter>> m_iter_pairs;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty())
        m_iter_pairs.emplace_back(make_pair(v1.begin(), v1.end()));
        if (!v2.empty())
        m_iter_pairs.emplace_back(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        pair<VecIter, VecIter> cur_pair = m_iter_pairs.front();
        m_iter_pairs.pop_front();
        int reval = *(cur_pair.first);
        ++ cur_pair.first;
        if (cur_pair.first != cur_pair.second) {
            m_iter_pairs.push_back(cur_pair);
        }
        return reval;
    }

    bool hasNext() {
        return !m_iter_pairs.empty();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
 ```
