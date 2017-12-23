Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

##### Example 1:

```
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
```

##### Example 2:

```
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
```

##### Example 3:

```
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
```

### Solution 1

__O(n) time, O(1) space.__

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        // All three numbers begin with LONG_MIN.
        // LONG_MIN here also means that the number has been reassigned 
        // a meaningful value or not. We use long here because it is possible
        // the nums has INT_MIN.
        long low(LONG_MIN), mid(LONG_MIN), high(LONG_MIN);
        
        for (int num : nums) {
            if (num == low || num == mid || num == high) continue;
            if (num > high) {
                // Now we need shift all three
                low = mid;
                mid = high;
                high = num;
            } else if (num > mid) {
                // Shift low and mid
                low = mid;
                mid = num;
                
            } else if (num > low){ // num > low
                // Shift low
                low = num;
            }
        }
        
        return low != LONG_MIN ? low : high;
    }
};
```

### Solution 2

Since we only have 3 elements, insert/delete is constant time operations. 

__O(1) time, O(1) space.__

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> top3;
        for (int num : nums) {
            top3.insert(num);
            if (top3.size() > 3)
                top3.erase(top3.begin());
        }
        return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
    }
};
```
