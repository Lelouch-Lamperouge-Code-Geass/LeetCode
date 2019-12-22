Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
  
```
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
```

# Solution

### Analysis

Well, in fact the problem of next permutation has been studied long ago. From the [Wikipedia page](https://en.wikipedia.org/wiki/Permutation), in the 14th century, a man named Narayana Pandita gives the following classic and yet quite simple algorithm (with minor modifications in notations to fit the problem statement):

1. Begin with right side of the input vector, and goes backwards. Find the first index which makes nums[i] < nums[i + 1]. If no such index exists, then the input vector is sorted in NON-increasing order, just sort the vector and return.

2.  If such index exists, then nums{index + 1, end_index} is non-increasing, sort nums{index + 1, end_index} and make this range non-decreasing.

3. Find the smallest number in range nums{index + 1, end_index} which is larger than nums[index]. 

                                                                                                  

### Code

```java
class Solution {
     public void nextPermutation(int[] nums) {
        if (nums == null || nums.length == 0) return;

        int mark = nums.length - 1;
        while (mark > 0 && nums[mark - 1] >= nums[mark]) {
            -- mark;
        }

        reverseIntArray(nums, mark, nums.length - 1);

        if (mark == 0) return;


        int upperBoundIndex = getIndexOfUpperBoundValue(nums, mark, nums.length - 1, nums[mark - 1]);

        swap(nums, mark - 1, upperBoundIndex);
    }

    private void reverseIntArray(int[] nums, int beginIndex, int endIndex) {
        while (beginIndex < endIndex) {
            swap(nums, beginIndex++, endIndex--);
        }
    }

    private void swap(int[] nums, int index1, int index2) {
        int valueAtIndex1 = nums[index1];
        nums[index1] = nums[index2];
        nums[index2] = valueAtIndex1;
    }

    private int getIndexOfUpperBoundValue(int[] nums, int beginIndex, int endIndex, int value) {
        while (beginIndex <= endIndex) {
            int mid = beginIndex + (endIndex - beginIndex) / 2;
            if (nums[mid] > value) {
                endIndex = mid - 1;
            } else {
                beginIndex = mid + 1;
            }
        }

        return beginIndex;
    }
}
```
