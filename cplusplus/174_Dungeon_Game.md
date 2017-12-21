The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
  
  
```
-2(K)	  -3	  3
-5	   -10	  1
10	   30	    -5(P)
```

##### Notes:

* The knight's health has no upper bound.
* Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
  
# Solution
   
The princess is imprisoned in the bottomr-right corner, and we are asked to determine the knight's minimum initial health at top-left. It will be easier if we calculate the minimum health from bottom-right to top-left. 
  
We know that the knight can only move down or right.
  
Therefore, ``` min_hp[i][j] = std::min(min_hp[i+1][j],min_hp[i][j+1]) - dungeon[i][j]```, however we still need to make sure that min_hp[i][j] >= 1.    
 
In order to make our loop easier, I add a bottom frame and right frame and their initial values are all INT_MAX.  

__The time compleixty is O(row_size * col_size), the space complexity is also O(row_size * col_size) but it can be optimized to O(col_size).__
  
```cpp
class Solution {
public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    if (dungeon.empty()) return 1;
    const int m(dungeon.size()), n(dungeon[0].size());
    vector< vector<int> > min_hp(m+1,vector<int>(n+1,INT_MAX));
    min_hp[m][n-1] = min_hp[m-1][n] = 1;
    for (int i=m-1;i>=0;--i) {
      for (int j=n-1;j>=0;--j) {
        min_hp[i][j] = std::min(min_hp[i+1][j],min_hp[i][j+1]) - dungeon[i][j];
        min_hp[i][j] = std::max(1,min_hp[i][j]);
      }
    }
    return min_hp[0][0];
  }
};
```
