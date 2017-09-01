Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

# Thinking

This problem is asking for "least number of xxx", which is requiring an optimal solution.
First of all, we need to check whether it has __optimal strucutre__, which means that whether an optimal solution can be constructed efficiently from optimal solutions of its __subproblems__. In other words, if we already know the answers for all numbers between [0, n-1], can we get the answer for n based on the subproblems' answers?

In most cases, we can get an optimal solution by:
1. Greedy algorithm __only if__ it can be proved by induction that this is optimal at __each step__.
2. Dynamic programming, provided the problem exhibits __overlapping subproblems__.

If there are no appropriate greedy algorithms and the problem fails to exhibit overlapping subproblems, often a lengthy but straightforward search of the solution space is the best alternative.
 
> In computer science, a problem is said to have __overlapping subproblems__ if the problem can be broken down into subproblems which are reused several times or a recursive algorithm for the problem solves the same subproblem over and over rather than always generating new subproblems.



# Solution
  
```cpp  
class Solution {
public:
    int numSquares(int n) {
        static std::vector<int> least_square_sum_count = {0, 1};
        int num = least_square_sum_count.size();
        while (num <= n) {
            int min_val = INT_MAX;
            for (int val = 1; val * val <= num; ++val) {
                min_val = std::min(min_val, 1 + least_square_sum_count[num - val * val]);
            }
            least_square_sum_count.push_back(min_val);
            ++ num;
        }
        
        return least_square_sum_count[n];
    }
};
```
