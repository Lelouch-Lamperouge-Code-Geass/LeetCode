Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

##### Note:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

##### Hint:

* Could you do it in-place with O(1) extra space?
* Related problem: [Reverse Words in a String II](https://leetcode.com/problems/reverse-words-in-a-string-ii/)


# Solution

### Solution 1

__Time complexity: O(n). Space complexity: O(1).__

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // Need to mod k against nums.size() fist
        k = k % nums.size();
        //reverse all elements
        std::reverse(nums.begin(),nums.end());
        //reverse [0, k - 1]
        std::reverse(nums.begin(),nums.begin() + k);
        //reverse [k, end)
        std::reverse(nums.begin() + k,nums.end());
    }
};
```

### Solution 2

Every swap will put one number into its correct position, so the running time is O(n).

For example,

```
at first, nums[] is [1,2,3,4,5,6,7], n is 7, k is 3

after first outer loop, nums[] is [4,1,2,3], n is 4, k is 3

after second outer loop, nums[] is [4], n is 1, k is 0

loop ends.
```

We are basically keeping put k numbers from the end at the right positions every inner loop.

__Time complexity: O(n). Space complexity: O(1).__

```cpp
class Solution { 
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        for (int start = 0; k %= n; n -= k, start += k) {
            for (int i = 0; i < k; i++) {
                swap(nums[start + i], nums[start + n - k + i]);
            }
        }
    }
}; 
```
