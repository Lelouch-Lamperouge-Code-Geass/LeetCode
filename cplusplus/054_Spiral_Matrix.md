Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
```
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
```

# Solution

This is a very simple and easy to understand solution. I traverse right and increment rowBegin, then traverse down and decrement colEnd, then I traverse left and decrement rowEnd, and finally I traverse up and increment colBegin.

The only tricky part is that when I traverse left or up I have to check whether the row or col still exists to prevent duplicates. 

### Solution when row size and colume size are both within integer range
```cpp
class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return vector<int>();
    vector<int> res;
    int row_size(matrix.size()), col_size(matrix[0].size());
    int start_row(0),end_row(row_size-1),start_col(0),end_col(col_size-1);

    while (start_row<=end_row && start_col<=end_col) {
      // top row
      for (int i=start_col;i<=end_col;++i) res.push_back(matrix[start_row][i]);
      ++ start_row;
      if (start_row>end_row) break;

      // right-most column
      for (int i=start_row;i<=end_row;++i) res.push_back(matrix[i][end_col]);
      -- end_col;
      if (start_col>end_col) break;

      // bottom row
      for (int i=end_col;i>=start_col;--i) res.push_back(matrix[end_row][i]);
      -- end_row;
      if (start_row>end_row) break;

      // left-most column
      for (int i=end_row;i>=start_row;--i) res.push_back(matrix[i][start_col]);
      ++ start_col;
      if (start_col>end_col) break;
    }
    return res;
  }
};
```

### Solution when std::size_t is required
```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return vector<int>();
        
        vector<int> reval;
        std::size_t start_row(0), end_row(matrix.size() - 1),
        start_col(0), end_col(matrix[0].size() - 1);
        
        while (start_row <= end_row && start_col <= end_col) {
            // strip first row off
            for (std::size_t i = start_col; i <= end_col; ++i) {
                reval.emplace_back(matrix[start_row][i]);
            }
            ++ start_row;
            if (start_row > end_row) break;
            
            // strip last column off
            for (std::size_t i = start_row; i <= end_row; ++i) {
                reval.emplace_back(matrix[i][end_col]);
            }
            if (end_col == 0 || start_col == end_col) break;
            -- end_col;
            
            // strip last row off
            if (start_row > end_row) break;
            for (std::size_t i = end_col + 1; i-- > start_col; ) {
                reval.emplace_back(matrix[end_row][i]);
            }
            if (end_row == 0 || start_row == end_row) break;
            -- end_row;
            
            // strip first column
            if (start_col > end_col) break;
            for (std::size_t i = end_row + 1; i-- > start_row; ) {
                reval.emplace_back(matrix[i][start_col]);
            }
            ++ start_col;
        }
        
        return reval;
    }
};
```
