Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.
  
# Solution  

### Solution 1
  
```cpp  
class Solution {
public:
    bool isHappy(int n) {
        if (n <= 0) return false;
        
        std::unordered_set<int> visited;
        
        while (n != 1) {
            visited.insert(n);
            
            int square_sum(0);
            while (n) {
                square_sum += std::pow(n % 10, 2);
                n /= 10;
            }
            
            if (visited.count(square_sum) != 0) {
                return false;
            } else {
                n = square_sum;
            }
        }
        
        return true;
    }
};
```

### Solution 2

We can simply adapt the Floyd Cycle detection algorithm.
  
If it is a happy number than it will stay at one and the slow pointer will eventually catch up. On the other hand, there must be a recurring number.  

```cpp
class Solution {
public:
  int digitSquareSum(int n) {
    int sum = 0, tmp;
    while (n) {
      tmp = n % 10;
      sum += tmp * tmp;
      n /= 10;
    }
    return sum;
  }

  bool isHappy(int n) {
    int slow, fast;
    slow = fast = n;
    do {
      slow = digitSquareSum(slow);
      fast = digitSquareSum(fast);
      fast = digitSquareSum(fast);
    } while(slow != fast);
    if (slow == 1) return true;
    else return false;
  }
};
```
