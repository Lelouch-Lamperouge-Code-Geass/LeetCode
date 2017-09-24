Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:    

```
nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].
```

Example 2:  


```
nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
```

# Solution

To get max length of increasing sequences:

1. Do DFS from every cell
2. Compare every 4 direction and skip cells that are out of boundary or smaller
3. Get matrix max from every cell's max
4. Use matrix[x][y] <= matrix[i][j] so we don't need a visited[m][n] array

The key is to cache the distance because it's highly possible to revisit a cell

__time complexity is O(m* n). Every element in the matrix can be only visited once cuz we use the cache.__  
  
```cpp
class Solution {
public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;
    const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
    vector<vector<int>> memoization(row_size, vector<int>(col_size,0));
    int reval(0);
    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        reval = std::max(reval, LongestPathForCell(matrix,i,j,memoization));
      }
    }
    return reval;
  }

  int LongestPathForCell(vector<vector<int>>& matrix, std::size_t row, std::size_t col,
                         vector<vector<int>> & memoization) {
    if (memoization[row][col] != 0) return memoization[row][col];
    int reval(1);
    int cur_val = matrix[row][col];
    matrix[row][col] = INT_MIN;
    if(row>0 && cur_val < matrix[row-1][col])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row-1, col, memoization));
    if(row+1<matrix.size() && cur_val < matrix[row+1][col])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row+1, col, memoization));
    if(col>0 && cur_val < matrix[row][col-1])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row, col-1, memoization));
    if(col+1<matrix[0].size() && cur_val < matrix[row][col+1])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row, col+1, memoization));
    matrix[row][col] = cur_val; // revert back
    memoization[row][col] = reval; // Memoize the result
    return reval;
  }
};
```

An alternative style.

```cpp
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        const std::size_t m(matrix.size()), n(matrix[0].size());
        vector<vector<int>> memoization(m, vector<int>(n, 0));
        std::size_t max_len(0);
        for (std::size_t i = 0; i < m; ++i) {
            for (std::size_t j = 0;  j < n; ++j) {
                max_len = std::max( max_len, dfs(matrix, memoization, i, j));
            }
        }
        return max_len;
    }
private:
    std::size_t dfs(vector<vector<int>> &matrix,
                vector<vector<int>> &memoization,
                std::size_t row,
                std::size_t col) {
        if (memoization[row][col] != 0) return memoization[row][col];
        static vector<pair<int, int>> move = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
        const std::size_t m(matrix.size()), n(matrix[0].size());
        std::size_t cur_len(1);
        for (const pair<int, int> &item : move) {
            std::size_t next_row = row + item.first;
            std::size_t next_col = col + item.second;

            if (next_row < m && next_col < n && matrix[next_row][next_col] > matrix[row][col]) {
                cur_len = std::max(cur_len, 1 + dfs(matrix, memoization, next_row, next_col));
            }
        }
        memoization[row][col] = cur_len;
        return cur_len;
    }
};
```

# Knowledge

### What is difference between memoization and dynamic programming?

Memoization is a term describing an optimization technique where you cache previously computed results, and return the cached result when the same computation is needed again.

Dynamic programming is a technique for solving problems recursively and is applicable when the computations of the subproblems overlap.

Dynamic programming is typically implemented using tabulation, but can also be implemented using memoization. So as you can see, neither one is a "subset" of the other.

A reasonable follow-up question is: What is the difference between tabulation (the typical dynamic programming technique) and memoization?

When you solve a dynamic programming problem using tabulation you solve the problem "bottom up", i.e., by solving all related sub-problems first, typically by filling up an n-dimensional table. Based on the results in the table, the solution to the "top" / original problem is then computed.

If you use memoization to solve the problem you do it by maintaining a map of already solved sub problems. You do it "top down" in the sense that you solve the "top" problem first (which typically recurses down to solve the sub-problems).

### Summary

If all subproblems must be solved at least once, a bottom-up dynamic-programming algorithm usually outperforms a top-down memoized algorithm by a constant factor : 
* No overhead for recursion and less overhead for maintaining table  
* There are some problems for which the regular pattern of table accesses in the dynamic-programming algorithm can be exploited to reduce the time or space requirements even further   

If some subproblems in the subproblem space need not be solved at all, the memoized solution has the advantage of solving only those subproblems that are definitely required
