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


We use threee variables to store the first-max, second-max and third-max numbers.

We initialize three variables ```first_max```, ```second_max```,  ```third_max``` begin with LONG_MIN. LONG_MIN here means that the number doesn't has a meaningful value yet. We use ```LONG_MIN``` here because it is possible the nums has ```INT_MIN```  and it is the third-maximum-number. 

For example, if we initialize these three numbers with ```INT_MIN```, it won't pass the case for ```[1,2,-2147483648]```, since in this case the third maximum number is ```-2147483648```.

__Note that the third maximum here means the third maximum distinct number , and the description of this problem is so bad that it doesn't mention it at all, and instead added a note on the third example.__

Since we are required to find the thrid __distinct__ number, we need to ignore all the numbers which are the same as ```first_max```, ```second_max```,  ```third_max```.

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long first_max(LONG_MIN), second_max(LONG_MIN), third_max(LONG_MIN);
        
        for (int num : nums) {
            if (num == first_max || num == second_max || num == third_max) continue;
            if (num > first_max) { // num > first_max
                // Now we need shift all three
                third_max= second_max;
                second_max = first_max;
                first_max = num;
            } else if (num > second_max) { // first_max > num > second_max
                third_max = second_max;
                second_max = num;
            } else if (num > third_max) { // second_max > num > third_max
                third_max = num;
            }
        }
        
        return third_max != LONG_MIN ? third_max : first_max;
    }
};
```

### Solution 2

We can use a min-heap to store the maximum numbers so far. We keep adding numbers to this min-heap and if its size is more than 3, we then pop the minimum number out.

Since we only have 3 elements, insert/delete is constant time operations for this min-heap. 

__O(1) time, O(1) space.__

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> top3; // min-heap
        for (int num : nums) {
            top3.insert(num);
            if (top3.size() > 3) { // Erase the minimum number at top
                top3.erase(top3.begin());
             }
        }
        return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
    }
};
```
