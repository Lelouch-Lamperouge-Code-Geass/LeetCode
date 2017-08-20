Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.

Example 1:  
```
nums = [1, 3], n = 6
Return 1.

Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
```

Example 2:  
```
nums = [1, 5, 10], n = 20
Return 2.
The two patches can be [2, 4].
```

Example 3:  
```
nums = [1, 2, 2], n = 5
Return 0.
```


# Solution

The question asked for the "__minimum__ number of patches required". In other words, it asked for an __optimal solution__. __Lots of problems involving optimal solution can be solved by dynamic programming and/or greedy algorithm.__ I started with greedy algorithm which is conceptually easy to design. Typically, a greedy algorithm needs selection of best moves for a subproblem. So what is our best move?

Think about this example: nums = [1, 2, 3, 9]. We naturally want to iterate through nums from left to right and see what we would discover. After we encountered 1, we know 1...1 is patched completely. After encountered 2, we know 1...3 (1+2) is patched completely. After we encountered 3, we know 1...6 (1+2+3) is patched completely. After we encountered 9, the smallest number we can get is 9. So we must patch a new number here so that we don't miss 7, 8. To have 7, the numbers we can patch is 1, 2, 3 ... 7. Any number greater than 7 won't help here. Patching 8 will not help you get 7. So we have 7 numbers (1...7) to choose from. I hope you can see number 7 works best here because if we chose number 7, we can move all the way up to 1+2+3+7 = 13. (1...13 is patched completely) and it makes us reach n as quickly as possible. After we patched 7 and reach 13, we can consider last element 9 in nums. Having 9 makes us reach 13+9 = 22, which means 1...22 is completely patched. If we still did't reach n, we can then patch 23, which makes 1...45 (22+23) completely patched. We continue until we reach n.

### Solution one

Let miss be the smallest sum in [0,n] that we might be missing. Meaning we already know we can build all sums in [0,miss). Then if we have a number num <= miss in the given array, we can add it to those smaller sums to build all sums in [0,miss+num). If we don't, then we must add such a number to the array, and it's best to add miss itself, to maximize the reach.

##### Example  
```
Let's say the input is nums = [1, 2, 4, 13, 43] and n = 100. 

We need to ensure that all sums in the range [1,100] are possible.

Using the given numbers 1, 2 and 4, we can already build all sums from 0 to 7, i.e., the range [0,8). 
But we can't build the sum 8, and the next given number (13) is too large. 
So we insert 8 into the array. Then we can build all sums in [0,16).

Do we need to insert 16 into the array? No! We can already build the sum 3, 
and adding the given 13 gives us sum 16. We can also add the 13 to the other sums, extending our range to [0,29).

And so on. The given 43 is too large to help with sum 29, so we must insert 29 into our array. 
This extends our range to [0,58). But then the 43 becomes useful and expands our range to [0,101). 
At which point we're done.
```

__In summary, when cur_num is within [0,missing), we don't need add number at all and can extend the range to [0, missing + cur_number). We only need add number when cur_number is large than missing, and the best candidate is the missing number itself.__

```cpp
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        std::size_t miss(1), index(0), added(0);
        
        // [1, miss) represents the consecutive interval we can build right now
        while (miss <= n) {
            if (index < nums.size() && nums[index] <= miss) {
              // When number <= miss, its can extend exsiting range.
                miss += nums[index++];
            } else {
              // When number > miss, we need fill the gap.
              // The best way is to add the missing number so that we can maximum the range.
                ++ added;
                miss += miss;
            }
        }
        
        return added;
    }
};
```
