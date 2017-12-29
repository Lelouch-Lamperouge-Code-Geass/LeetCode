There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

# Solution



```cpp
int minCost(vector<vector<int>>& costs) {
    int n = costs.size();
    for (int i = 1; i < n; i++) {
        costs[i][0] += std::min(costs[i - 1][1], costs[i - 1][2]);
        costs[i][1] += std::min(costs[i - 1][0], costs[i - 1][2]);
        costs[i][2] += std::min(costs[i - 1][0], costs[i - 1][1]);
    }
    return (n == 0) ? 0 : (std::min(costs[n - 1][0], std::min(costs[n - 1][1], costs[n - 1][2])));
}
```

We can optimize above solution to have O(1) space complexity.

```cpp
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int paint_red(0), paint_blue(0), paint_green(0);

        for (const std::vector<int> &cur_cost : costs) {
            int pre_red = paint_red, pre_blue = paint_blue, pre_green = paint_green;
            
            paint_red = std::min(pre_blue, pre_green) + cur_cost[0];
            paint_blue = std::min(pre_red, pre_green) + cur_cost[1];
            paint_green = std::min(pre_red, pre_blue) + cur_cost[2];
            
        }
        
       return std::min(paint_red, std::min(paint_blue, paint_green));
    }
};
```

# Knowledge

In computer science, mathematics, management science, economics and bioinformatics, __dynamic programming (also known as dynamic optimization) is a method for solving a complex problem by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions__. The next time the same subproblem occurs, instead of recomputing its solution, one simply looks up the previously computed solution, thereby saving computation time at the expense of a (hopefully) modest expenditure in storage space. (Each of the subproblem solutions is indexed in some way, typically based on the values of its input parameters, so as to facilitate its lookup.) The technique of storing solutions to subproblems instead of recomputing them is called __"memoization"__.

Dynamic programming algorithms are often used for optimization. A dynamic programming algorithm will examine the previously solved subproblems and will combine their solutions to give the best solution for the given problem. In comparison, a greedy algorithm treats the solution as some sequence of steps and picks the locally optimal choice at each step. __Using a greedy algorithm does not guarantee an optimal solution, because picking locally optimal choices may result in a bad global solution, but it is often faster to calculate.__ Some greedy algorithms (such as Kruskal's or Prim's for minimum spanning trees) are however proven to lead to the optimal solution.

From Wikipedia, dynamic programming is a method for solving a complex problem by breaking it down into a collection of simpler subproblems. As it said, _it’s very important to understand that the core of dynamic programming is breaking down a complex problem into simpler subproblems_.

Dynamic programming is very similar to recursion. But when subproblems are solved for multiple times, dynamic programming utilizes memorization techniques (usually a memory table) to store results of subproblems so that same subproblem won’t be solved twice.

* http://blog.gainlo.co/index.php/2015/10/22/a-step-by-step-guide-to-dynamic-programming/?utm_campaign=quora&utm_medium=What+are+systematic+ways+to+prepare+for+dynamic+programming%3F&utm_source=quora
