There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

# Solution

这道题是之前那道Paint House的拓展，那道题只让用红绿蓝三种颜色来粉刷房子，而这道题让我们用k种颜色，这道题不能用之前那题的解法，会TLE。这题的解法的思路还是用DP，但是在找不同颜色的最小值不是遍历所有不同颜色，而是用min1和min2来记录之前房子的最小和第二小的花费的颜色，如果当前房子颜色和min1相同，那么我们用min2对应的值计算，反之我们用min1对应的值，这种解法实际上也包含了求次小值的方法，感觉也是一种很棒的解题思路，参见代码如下：

```cpp
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        
        const std::size_t house_count(costs.size()), color_count(costs[0].size());
        
        std::vector<std::vector<int>> min_costs(house_count, std::vector<int>(color_count, INT_MAX));
        
        int min_one_color(-1), min_two_color(-1); // Record the color of minimal cost so far
        
        for (std::size_t house = 0; house < house_count; ++ house) {
            int pre_min_one_color = min_one_color, pre_min_two_color = min_two_color;
            min_one_color = -1, min_two_color = -1;
            for (int color = 0; color < color_count; ++ color) {
                if (color != pre_min_one_color) {
                    min_costs[house][color] = house == 0 ? costs[house][color] 
                            : min_costs[house - 1][pre_min_one_color] + costs[house][color];
                } else {
                    min_costs[house][color] = house == 0 ? costs[house][color] 
                        :min_costs[house - 1][pre_min_two_color] + costs[house][color];
                }
                
                if (min_one_color < 0 || min_costs[house][color] < min_costs[house][min_one_color]) {
                    min_two_color = min_one_color;
                    min_one_color = color;
                } else if (min_two_color < 0 || min_costs[house][color] < min_costs[house][min_two_color]) {
                    min_two_color = color;
                }
            }

        }
        
        return min_costs[house_count - 1][min_one_color];
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
