Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

__Follow up__:  
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

# Solution

```
[ , red]  represents red colors
[red + 1, i - 1] represents white colors
[i, blue - 1] colors have not been checked
[blue, ] represents blue colors 
```

The pitfall is that we can't move i forward if it's value is 0 or 2.
And it is possible that after swap(nums[i], nums[--blue]), nums[i] is still 2 or 0.
 
```cpp
class Solution {
public:
  void sortColors(vector<int>& nums) {
    int red(-1), blue(nums.size());

    for (int i=0;i<blue;) {
      if (i>red && nums[i]==0) {
        std::swap(nums[++red],nums[i]);
      } else if(i<blue &&nums[i]==2) {
        std::swap(nums[--blue],nums[i]);
      } else {
        // nums[i]==1 or can't swap i with red and blue anymore
        ++ i;
      }
    }
  }
};
```

