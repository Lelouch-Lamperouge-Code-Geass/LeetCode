Implement int sqrt(int x).

Compute and return the square root of x.
  
  
# Solution

The sequence 1, 2, ... , n has no duplication.
Near the very end, closest step, before while loop, left = mid = right.
* In while, If mid < sqrt(x), left = mid + 1 executed, right pointer is not moving, and right is the answer.
* If while, If mid > sqrt(x), right = mid - 1 executed, right pointer shifts left 1, closest to sqrt(x), right is also the answer.

```cpp
class Solution {
public:
    int mySqrt(int x) {
        if (x < 0) throw std::invalid_argument("Input can't be negative");
        if (x == 0) return 0;
        
        int low(1), high(x/2 + 1);
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (mid > x / mid) {
                high = mid - 1;
            } else if (mid < x / mid) {
                low = mid + 1;
            } else { // square == x
                return mid;
            }
        }
        
        return high;
    }
};
```
