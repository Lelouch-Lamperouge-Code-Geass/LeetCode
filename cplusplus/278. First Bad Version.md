You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

# Solution
For binary search problems, many people try to remember or guess off-by-ones, correct termination conditions and pre-checks instead of understanding invariant of the algorithm. Some people stick to a specific implementation of binary search.

But once you have an __invariant__ and follow it, you won't make a mistake and will be able to write and understand any kind of binary search. Moreover, you will be able to find bugs easily.

Example: I want to find first element >=X in a sorted array. Invariant: I have a interval from L to R such that a[L]<X and a[R]>=X. Then, after I check element M in between, I set either L or R to M, preserving the invariant. Loop is terminated when answer is obvious - that is, there are no elements strictly between L and R, and answer is R. Oh, and initialization is easy as well: I can assume that my array has -inf before the beginning and +inf after the end. As I will never read these elements, I just initialize L=-1 and R=length of the array.

Another example: I want to find element X. Invariant: a[L]<X and a[R]>X. Initialization: same. If a[M] is X, I return answer, otherwise I change L or R. If there are no elements between L and R, there is no answer.

```cpp
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);


class Solution {
public:
    int firstBadVersion(int n) {
        int low(1), high(n);      
        // Invariant: make sure the first bad version always within [low,high]
        while (low <  high) {
            int mid = low + (high - low) / 2;
            
            if (!isBadVersion(mid)) { 
                low = mid + 1; // first bad version is still within [low,high] 
            } else { 
                high = mid; // first bad version is still within [low,high] 
            }
        }
        
        return low; 
    }
};
```
