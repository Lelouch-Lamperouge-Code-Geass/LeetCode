Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,

```
add(1); add(3); add(5);
find(4) -> true
find(7) -> false
```

# Solution

The big data test only have the condition that lots of add and few find. In fact, there has to be one operation's time complexity is O(n) and the other is O(1), no matter add or find. So clearly there's trade off when solve this problem, prefer quick find or quick add.

If consider more find and less add or we only care time complexity in finding.For example, add operation can be pre-done.


### Solution 1

__Add O(n), find O(1).__

```cpp
class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        if (m_num.count(number) == 0) { // First time
            // Add its sum with each previous numbers
            for (int temp : m_num) {
                m_sum.insert(temp + number);
            }
            // Add number itself
            m_num.insert(number);
        } else { // Not first time 
           m_sum.insert(number * 2); 
        }
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        return m_sum.count(value) != 0;
    }
private:
    std::unordered_set<int> m_num;
    std::unordered_set<int> m_sum;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */
 ```
 
### Solution 2

__Add O(1), find O(N).__

We can cache the find fuction here.
 
 ```cpp
 class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        ++ m_num_counter[number];
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for (const auto &pair : m_num_counter) {
            if (value == pair.first * 2) {
                if (pair.second >= 2) return true;
            } else {
                if (m_num_counter.count(value - pair.first) > 0) return true;
            }
        }
        return false;
    }
private:
    std::unordered_map<int, int> m_num_counter;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */
 ```
 
