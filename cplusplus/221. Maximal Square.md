Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:
```
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
```  
Return 4.


# Solution
Well, this problem desires for the use of dynamic programming. They key to any DP problem is to come up with the state equation. In this problem, we define the state to be the maximal size of the square that can be achieved at point (i, j), denoted as P[i][j]. Remember that we use size instead of square as the state (square = size^2). (Using square instead of side length still works, but you will find that you still need square side length when calculate it during dynamic programming),

Now let's try to come up with the formula for P[i][j].

First, it is obvious that for the topmost row (i = 0) and the leftmost column (j = 0), P[i][j] = matrix[i][j]. This is easily understood. Let's suppose that the topmost row of matrix is like [1, 0, 0, 1]. Then we can immediately know that the first and last point can be a square of size 1 while the two middle points cannot make any square, giving a size of 0. Thus, P = [1, 0, 0, 1], which is the same as matrix. The case is similar for the leftmost column. Till now, the boundary conditions of this DP problem are solved.

Let's move to the more general case for P[i][j] in which i > 0 and j > 0. First of all, let's see another simple case in which matrix[i][j] = 0. It is obvious that P[i][j] = 0 too. Why? Well, since matrix[i][j] = 0, no square will contain matrix[i][j]. According to our definition of P[i][j], P[i][j] is also 0.

Now we are almost done. The only unsolved case is matrix[i][j] = 1. Let's see an example.

Suppose matrix = [[0, 1], [1, 1]], it is obvious that P[0][0] = 0, P[0][1] = P[1][0] = 1, what about P[1][1]? Well, to give a square of size larger than 1 in P[1][1], all of its three neighbors (left, up, left-up) should be non-zero, right? In this case, the left-up neighbor P[0][0] = 0, so P[1][1] can only be 1, which means that it contains the square of itself.

Now you are near the solution. In fact, P[i][j] = min(P[i - 1][j], P[i][j - 1], P[i - 1][j - 1]) + 1 in this case.

Taking all these together, we have the following state equations.

* P[0][j] = matrix[0][j] (topmost row);
* P[i][0] = matrix[i][0] (leftmost column);
* For i > 0 and j > 0: if matrix[i][j] = 0, P[i][j] = 0; if matrix[i][j] = 1, P[i][j] = min(P[i - 1][j], P[i][j - 1], P[i - 1][j - 1]) + 1.
  
Putting them into codes, and maintain a variable maxsize to record the maximum size of the square we have seen, we have the following (unoptimized) solution.
  
```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
        vector<vector<int>> max_len (row_size, vector<int>(col_size, 0));
        
        int max_square_len(0);
        
        for (std::size_t row = 0; row < row_size; ++row) {
            for (std::size_t col = 0; col < col_size; ++col) {
                if (row == 0 || col == 0) {
                    max_len[row][col] = matrix[row][col] == '1' ? 1 : 0;
                } else {
                    if ('1' == matrix[row][col]) {
                        max_len[row][col] = 1 + std::min(max_len[row-1][col-1],
                            std::min(max_len[row-1][col], max_len[row][col-1]) );
                    }
                }
                
                max_square_len = std::max(max_square_len, max_len[row][col]);
                
            }
        }
        
        return max_square_len * max_square_len;
    }
};
```

Can be optimized to O(n) space complexity.

This solution need to be check again, not working.

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        const std::size_t m(matrix.size()), n(matrix[0].size());
        vector<std::size_t> max_len(n, 0);
        
        std::size_t max_square_len(0), diagonal_neighbor(0);
        for (std::size_t i = 0; i < m; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                int temp = max_len[j];
                if (i == 0 || j == 0) {
                    max_len[j] = matrix[i][j] == '1' ? 1 : 0;
                } else {
                    if (matrix[i][j] == '1') {
                        max_len[j] = 1 + std::min(diagonal_neighbor, 
                                                  std::min(max_len[j], max_len[j-1]));
                    }
                }
                diagonal_neighbor = temp;
                max_square_len = std::max(max_square_len, max_len[j]);

            }
        }
        
        return max_square_len * max_square_len;
    }
};
```
