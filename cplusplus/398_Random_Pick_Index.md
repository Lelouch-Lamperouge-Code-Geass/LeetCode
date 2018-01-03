Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

```
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. 
// Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);
```

# Solution

### Solution 1, Reservoir Sampling

Even though this solution passed leetcode tests, I don't think it is correct.

Because it is clearly stated that "The array size can be very large.", we should not store the numbers in member variable.

```cpp
class Solution {
public:
    Solution(vector<int> nums) : m_nums(nums){
    }
    
    int pick(int target) {
        std::size_t pos(-1), count(0);
        for (std::size_t i = 0, n = m_nums.size(); i < n; ++i) {
            if (m_nums[i] == target) {
                ++ count;
                if (rand() % count == 0) { // make sure have probability 1/count to replace the previous index
                    pos = i;
                }
            }
        }
        
        return pos;
    }
private:
    vector<int> m_nums;
};
```

 I tried to save the iterators only but did not pass the leetcode tests, it might be because that the input vector may have been destroyed.

__Below solution is not working!__
```cpp
class Solution {
public:
    Solution(vector<int> nums) {
        vec_begin = nums.begin();
        vec_end = nums.end();
    }
    
    int pick(int target) {
        vector<int>::iterator pos(vec_end);
        std::size_t count(0);
        for (vector<int>::iterator iter = vec_begin; iter != vec_end; ++iter) {
            if (*iter == target) {
                ++ count;
                if (random() % count == 0) {
                    pos = iter;
                }
            }
        }
        
        return pos - vec_begin;
    }
private:
    vector<int>::iterator vec_begin, vec_end;
};
```

Modify a little bit, then it works.

```cpp
class Solution {
public:
    Solution(vector<int> nums) :m_nums(nums){
        vec_begin = m_nums.begin();
        vec_end = m_nums.end();
    }
    
    int pick(int target) {
        vector<int>::iterator pos(vec_end);
        std::size_t count(0);
        for (vector<int>::iterator iter = vec_begin; iter != vec_end; ++iter) {
            if (*iter == target) {
                ++ count;
                if (rand() % count == 0) {
                    pos = iter;
                }
            }
        }
        
        return pos - vec_begin;
    }
private:
    vector<int> m_nums;
    vector<int>::iterator vec_begin, vec_end;
};
```
