Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:  

Given array A = [2,3,1,1,4]  

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

##### Note:  
  
You can assume that you can always reach the last index.

# Solution

This problem has a nice BFS structure. Let's illustrate it using the example nums = [2, 3, 1, 1, 4] in the problem statement. We are initially at position 0. Then we can move at most nums[0] steps from it. So, after one move, we may reach nums[1] = 3 or nums[2] = 1. So these nodes are reachable in 1 move. From these nodes, we can further move to nums[3] = 1 and nums[4] = 4. Now you can see that the target nums[4] = 4 is reachable in 2 moves.
  
  
```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        const int N(nums.size());
        if(N <= 1) return 0;
        int reval(0),reach(0),next_reach(0);
        for(int i = 0 ;i <= reach && i<N; ++i){
            next_reach = std::max(next_reach, i + nums[i]);
            if(i != N-1 && i == reach){
                ++ reval;
                reach = next_reach;
                if(reach >= N-1) break;
            }
        }
        return reval;
    }
};
```
