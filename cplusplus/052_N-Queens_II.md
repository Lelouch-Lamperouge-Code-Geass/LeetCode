
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
  
![alt](https://leetcode.com/static/images/problemset/8-queens.png)
  
# Solution
    
```cpp
class Solution {
public:
    int totalNQueens(int n) {
        if (n <= 0) return 0;
        
        std::vector<bool> col_marker(n, false), diag_45_marker(n, false), diag_135_marker(n, false);
        
        int reval(0);
        fillBoardWithBacktracking(reval, 0, n, 
                                  col_marker, diag_45_marker, diag_135_marker);
        return reval;
    }
private:
    void fillBoardWithBacktracking(int &solution_count,
                                  const int row,
                                  const int n,
                                  std::vector<bool> &col_marker,
                                  std::vector<bool> &diag_45_marker,
                                  std::vector<bool> &diag_135_marker) {
        if (row == n) { // Complete!
            ++ solution_count;
        } else {
            // Try to fill every empty square on this row one by one
            for (int col = 0; col < n; ++col) {
                // Get index of diagonal markers based on row and col
                int k1 = n + col - row - 1, k2 = row + col;
                if (!col_marker[col] && !diag_45_marker[k1] && !diag_135_marker[k2]) {
                    col_marker[col] = diag_45_marker[k1] = diag_135_marker[k2] = true;
                    fillBoardWithBacktracking(solution_count, row + 1, n, 
                                              col_marker, diag_45_marker, diag_135_marker);
                    col_marker[col] = diag_45_marker[k1] = diag_135_marker[k2] = false; // revert back
                }
            }
        }
    }
};
```
