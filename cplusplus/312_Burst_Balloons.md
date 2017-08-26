Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.  

Find the maximum coins you can collect by bursting the balloons wisely.  

Note:   
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.   
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100  

##### Example:

Given [3, 1, 5, 8]

Return 167

```
    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
```   

# Knowledge

In computer science, a problem is said to have __optimal substructure__ if an optimal solution can be constructed efficiently from optimal solutions of its subproblems. This property is used to determine the usefulness of dynamic programming and greedy algorithms for a problem.

Typically, a greedy algorithm is used to solve a problem with optimal substructure if it can be proved by induction that this is optimal at each step. Otherwise, provided the problem exhibits overlapping subproblems as well, dynamic programming is used. If there are no appropriate greedy algorithms and the problem fails to exhibit overlapping subproblems, often a lengthy but straightforward search of the solution space is the best alternative.

Typical way to solve a problem with optimal substructure:

* Greedy algorithm  
* Dynamic programming  

# Solution

##### Be Naive First

When I first get this problem, it is far from dynamic programming to me. I started with the most naive idea the backtracking.

We have n balloons to burst, which mean we have n steps in the game. In the i th step we have n-i balloons to burst, i = 0~n-1. Therefore we are looking at an algorithm of O(n!). Well, it is slow, probably works for n < 12 only.

Of course this is not the point to implement it. We need to identify the redundant works we did in it and try to optimize.

Well, we can find that for any balloons left the maxCoins does not depends on the balloons already bursted. This indicate that we can use memorization (top down) or dynamic programming (bottom up) for all the cases from small numbers of balloon until n balloons. How many cases are there? For k balloons there are C(n, k) cases and for each case it need to scan the k balloons to compare. The sum is quite big still. It is better than O(n!) but worse than O(2^n).

##### Better idea

We then think can we apply the divide and conquer technique? After all there seems to be many self similar sub problems from the previous analysis.

Well, the nature way to divide the problem is burst one balloon and separate the balloons into 2 sub sections one on the left and one one the right. However, in this problem the left and right become adjacent and have effects on the maxCoins in the future.

Then another interesting idea come up. Which is quite often seen in dp problem analysis. That is reverse thinking. Like I said the coins you get for a balloon does not depend on the balloons already burst. Therefore
instead of divide the problem by the first balloon to burst, we divide the problem by the last balloon to burst.

Why is that? Because only the first and last balloons we are sure of their adjacent balloons before hand!

For the first we have nums[i-1]*nums[i]*nums[i+1] for the last we have nums[-1]*nums[i]*nums[n].

OK. Think about n balloons if i is the last one to burst, what now?

We can see that the balloons is again separated into 2 sections. But this time since the balloon i is the last balloon of all to burst, the left and right section now has well defined boundary and do not affect each other! Therefore we can do either recursive method with memoization or dp.

##### Final

Here comes the final solutions. Note that we put 2 balloons with 1 as boundaries and also burst all the zero balloons in the first round since they won't give any coins.  
The algorithm runs in __O(n^3)__ which can be easily seen from the 3 loops in dp solution.  


```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int N = nums.size();
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
    
        // rangeValues[i][j] is the maximum # of coins that can be obtained
        // by popping balloons only in the range [i,j]
        vector<vector<int>> rangeValues(nums.size(), vector<int>(nums.size(), 0));
        
        // build up from shorter ranges to longer ranges
        for (int len = 1; len <= N; ++len) {
            for (int start = 1; start + len <= N + 1; ++start) {
                int end = start + len - 1;
                // calculate the max # of coins that can be obtained by
                // popping balloons only in the range [start,end].
                // consider all possible choices of final balloon to pop
                int bestCoins = 0;
                for (int last_burst = start; last_burst <= end; ++last_burst) {
                    int coins = rangeValues[start][last_burst-1] + rangeValues[last_burst+1][end]; // coins from popping subranges
                    coins += nums[start-1] * nums[last_burst] * nums[end+1]; // coins from final pop
                    if (coins > bestCoins) bestCoins = coins;
                }
                rangeValues[start][end] = bestCoins;
            }
        }
        return rangeValues[1][N];
    }
};
```
