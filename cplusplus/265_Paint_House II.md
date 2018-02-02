There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

__Note:__  
All costs are positive integers.

__Follow up:__  
Could you solve it in O(nk) runtime?

# Solution

For every house, we know that we can paint k colors. 

Let paint_cost[i][j] represents the cost of paint current house i with color j, and all previous houses have been painted.
The minimal paint cost with color j, in this case, is derived from the minimal cost of paint house i - 1, but we need to gurantee that we should use different colors here.

Therefore, we use two paramter, pre_min_one to represnts the color we used to paint previous house which yeild the minimal cost for previous house; pre_min_two to represnts the color we used to pain previous house which gield the second minimial cost for previous house.


这道题是之前那道Paint House的拓展，那道题只让用红绿蓝三种颜色来粉刷房子，而这道题让我们用k种颜色，这道题不能用之前那题的解法，会TLE。这题的解法的思路还是用DP，但是在找不同颜色的最小值不是遍历所有不同颜色，而是用min1和min2来记录之前房子的最小和第二小的花费的颜色，如果当前房子颜色和min1相同，那么我们用min2对应的值计算，反之我们用min1对应的值，这种解法实际上也包含了求次小值的方法，感觉也是一种很棒的解题思路，参见代码如下：

```cpp
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        
        const int num_of_house = costs.size(), number_of_color = costs[0].size();
        
        std::vector<std::vector<int>> min_costs(num_of_house, std::vector<int>(number_of_color, INT_MAX));
        
        int pre_min1_color(-1), pre_min2_color(-1);
        
        for (int color = 0; color < number_of_color; ++color) {
            min_costs[0][color] = costs[0][color];
            
            if (pre_min1_color == -1 
                || min_costs[0][color] < min_costs[0][pre_min1_color]) {
                pre_min2_color = pre_min1_color;
                pre_min1_color = color;
            } else if (pre_min2_color == -1  
                || min_costs[0][color] < min_costs[0][pre_min2_color]) {
                pre_min2_color = color;
            }
        }
        
        for (int house = 1; house < num_of_house; ++house) {
            // Now let's try to paint current house with different colors.
            // And we also need to record the color(index) of the minimum cost
            // and the second minimum cost.
            int cur_min1_color(-1), cur_min2_color(-1);
            for (int color = 0; color < number_of_color; ++color) {
                // To paint this color, in order to minimize the cost,
                // we need to derive from the previous minimum cost color if we can,
                // otherwise , derive from the previous second minimum cost color.
                if (color != pre_min1_color) {
                    min_costs[house][color] 
                        = min_costs[house - 1][pre_min1_color] + costs[house][color];
                } else {
                    min_costs[house][color] 
                        = min_costs[house - 1][pre_min2_color] + costs[house][color];
                }
                
                if (cur_min1_color == -1 
                    || min_costs[house][color] < min_costs[house][cur_min1_color]) {
                    cur_min2_color = cur_min1_color;
                    cur_min1_color = color;
                } else if (cur_min2_color == -1 
                    || min_costs[house][color] < min_costs[house][cur_min2_color]) {
                    cur_min2_color = color;
                }
            }
            
            // Need to update these two variables.
            pre_min1_color = cur_min1_color;
            pre_min2_color = cur_min2_color;
            
        }
        
        return min_costs.back()[pre_min1_color];
    }
};
```

Simplify a little bit.

```cpp
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        int num_of_house = costs.size(), num_of_color = costs[0].size();
        vector<vector<int>> min_costs(num_of_house, vector<int>(num_of_color, INT_MAX));
        int pre_min_color(-1), pre_min2_color(-1);
        
        for (int house = 0; house < num_of_house; ++house) {
            int cur_min_color(-1), cur_min2_color(-1);
            
            for (int color = 0; color < num_of_color; ++color) {
                if (house == 0) {
                    min_costs[house][color] = costs[house][color];
                } else {
                    if (pre_min_color != color) {
                        min_costs[house][color] 
                            = min_costs[house - 1][pre_min_color] + costs[house][color];
                    } else {
                        min_costs[house][color] 
                            = min_costs[house - 1][pre_min2_color] + costs[house][color];
                    }
                }
                if (cur_min_color == -1 
                    ||  min_costs[house][color]  <  min_costs[house][cur_min_color] ) {
                    cur_min2_color = cur_min_color;
                    cur_min_color = color;
                } else if (cur_min2_color == -1 
                    ||  min_costs[house][color]  <  min_costs[house][cur_min2_color] ) {
                    cur_min2_color = color;
                } 
            }
            
            pre_min_color = cur_min_color;
            pre_min2_color = cur_min2_color;
        }
        
        return min_costs[num_of_house - 1][pre_min_color];
    }
};
```

下面这种解法不需要建立二维dp数组，直接用三个变量就可以保存需要的信息即可，参见代码如下：


```cpp
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int min1 = 0, min2 = 0, idx1 = -1;
        for (int i = 0; i < costs.size(); ++i) {
            int m1 = INT_MAX, m2 = m1, id1 = -1;
            for (int j = 0; j < costs[i].size(); ++j) {
                int cost = costs[i][j] + (j == idx1 ? min2 : min1);
                if (cost < m1) {
                    m2 = m1; m1 = cost; id1 = j;
                } else if (cost < m2) {
                    m2 = cost;
                }
            }
            min1 = m1; min2 = m2; idx1 = id1;
        }
        return min1;
    }
};
```
