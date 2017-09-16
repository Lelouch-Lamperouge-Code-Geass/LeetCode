Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

![alt](https://leetcode.com/static/images/courses/range_sum_query_2d.png)

The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

```
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
```

Note:   
1. You may assume that the matrix does not change.  
2. There are many calls to sumRegion function.  
3. You may assume that row1 ≤ row2 and col1 ≤ col2.  

# Solution

### Solution 1

Construct a 2D array sums[row+1][col+1]

(notice: we add additional blank row sums[0][col+1]={0} and blank column sums[row+1][0]={0} to remove the edge case checking), so, we can have the following definition

sums[i+1][j+1] represents the sum of area from matrix[0][0] to matrix[i][j].


```
sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +  

                        matrix[i-1][j-1]
```



```cpp
class NumMatrix {
private:
    int row, col;
    vector<vector<int>> sums;
public:
    NumMatrix(vector<vector<int>> &matrix) {
        row = matrix.size();
        col = row>0 ? matrix[0].size() : 0;
        sums = vector<vector<int>>(row+1, vector<int>(col+1, 0));
        for(int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++) {
                sums[i][j] = matrix[i-1][j-1] + 
                             sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] ;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2+1][col2+1] - sums[row2+1][col1] - sums[row1][col2+1] + sums[row1][col1];
    }
};
```

### Solution 2

Same as solution 1, just without additional row and column.

```cpp
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        m_range_sum = matrix;
        for (std::size_t i = 0, m = matrix.size(); i < m; ++i) {
            for (std::size_t j = 0, n = matrix[0].size(); j < n; ++j) {
                if (j > 0) m_range_sum[i][j] += m_range_sum[i][j-1];
                if (i > 0) m_range_sum[i][j] += m_range_sum[i-1][j];
                if (i>0 && j > 0) m_range_sum[i][j] -= m_range_sum[i-1][j-1];
            }
        }    
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int reval = m_range_sum[row2][col2];
        if (row1 > 0) reval -= m_range_sum[row1-1][col2];
        if (col1 > 0) reval -= m_range_sum[row2][col1 - 1];  
        if (row1 > 0 && col1 > 0) reval += m_range_sum[row1 - 1][col1 - 1];
        return reval;
    }
private:
    
    vector<vector<int>> m_range_sum;
};
```
