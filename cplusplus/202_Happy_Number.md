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

Earlier posts gave the algorithm but did not explain why it is valid mathematically, and this is what this post is about: present a "short" mathematical proof.

First of all, it is easy to argue that starting from a number I, if some value - say a - appears again during the process after k steps, the initial number I cannot be a happy number. Because a will continuously become a after every k steps.

Therefore, as long as we can show that there is a loop after running the process continuously, the number is not a happy number.

There is another detail not clarified yet: _For any non-happy number, will it definitely end up with a loop during the process? This is important, because it is possible for a non-happy number to follow the process endlessly while having no loop__

To show that a non-happy number will definitely generate a loop, we only need to show that for any non-happy number, all outcomes during the process are bounded by some large but finite integer N. If all outcomes can only be in a finite set (2,N], and since there are infinitely many outcomes for a non-happy number, there has to be at least one duplicate, meaning a loop!

Suppose after a couple of processes, we end up with a large outcome O1 with D digits where D is kind of large, say D>=4, i.e., O1 > 999 (If we cannot even reach such a large outcome, it means all outcomes are bounded by 999 ==> loop exists). We can easily see that after processing O1, the new outcome O2 can be at most ```9^2*D < 100D```, meaning that O2 can have at most 2+d(D) digits, where d(D) is the number of digits D have. It is obvious that 2+d(D) < D. We can further argue that O1 is the maximum (or boundary) of all outcomes afterwards. This can be shown by contradictory: Suppose after some steps, we reach another large number O3 > O1. This means we process on some number W <= 999 that yields O3. However, this cannot happen because the outcome of W can be at most 9^2*3 < 300 < O1.

https://discuss.leetcode.com/topic/42746/all-you-need-to-know-about-testing-happy-number

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
