Given an array and a value, remove all instances of that value __in-place__ and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

# Solution


```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len(0);
        
        for (int num : nums) {
            if (num != val) {
                nums[len++] = num;
            }
        }
        
        return len;
    }
};
```

# Knowledge

### What does In-place mean?

In computer science, an __in-place__ algorithm is an algorithm which transforms input using no auxiliary data structure. However a small amount of extra storage space is allowed for auxiliary variables. The input is usually overwritten by the output as the algorithm executes. In-place algorithm updates input sequence only through replacement or swapping of elements. An algorithm which is not in-place is sometimes called __not-in-place__ or __out-of-place__.

