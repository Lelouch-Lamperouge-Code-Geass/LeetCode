Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
  
##### Follow up:
  
Did you use extra space?  
A straight forward solution using O(mn) space is probably a bad idea.  
A simple improvement uses O(m + n) space, but still not the best solution.  
Could you devise a constant space solution?    

  
# Solution  

Using O(mn) space is to naive. Will not discuss that solution here.
  
  
This solution is uses O(m + n) space. We use two vectors, one row marker and one column marker.

Everytime we meet a zero element, mark the row_marker[i] and col_marker[j] to be ```true```(means it the row/column should be all '0'). 

Note that when we set matrix elements zero, we do it from bottom-right to top-left.

```cpp  
class Solution {
public:
  void setZeroes(vector<vector<int>>& matrix) {
    if(matrix.empty()) return;
    const std::size_t row_size(matrix.size()),col_size(matrix[0].size());

    vector<bool> zero_row(row_size,false), zero_col(col_size,false);

    for (std::size_t i=0;i<row_size;++i) {
      for (std::size_t j=0;j<col_size;++j) {
        if (matrix[i][j] == 0)
          zero_row[i] = zero_col[j] = true;
      }
    }

    for (int i=0;i<row_size;++i) {
      for (int j=0;j<col_size;++j) {
        if(zero_row[i] || zero_col[j])
          matrix[i][j] = 0;
      }
    }
  }
};
```


This solution use O(1).
  
My idea is simple: store states of each row in the first of that row, and store states of each column in the first of that column. Because the state of row0 and the state of column0 would occupy the same cell, I let it be the state of row0, and use another variable "col0" for column0. In the first phase, use matrix elements to set states in a top-down way. In the second phase, use states to set matrix elements in a bottom-up way.
  
```cpp  
class Solution {
public:
  void setZeroes(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    const std::size_t row_size(matrix.size()),col_size(matrix[0].size());
    int col0 = 1; // represents whether column 0 should be zeroes
    for (std::size_t i=0;i<row_size;++i) {
      if (matrix[i][0]==0) col0 = 0;
      
      // Note that here j begin with 1, why not 0?
      // Because if it begins with 0, then matrix[0][j] = 0 will
      // make matrix[0][0] = 0 and matrix[0][0] is used to state whether row 0 should
      // be all '0' or not.
      for (std::size_t j=1;j<col_size;++j) {
        if (matrix[i][j]==0) {
          matrix[i][0] = matrix[0][j] = 0;
        }
      }
    }
    
   // Here we set the matrix elements from bottom-right to top-left.
   // Basically, we are handling elements row by row from the last row.
   // If we want to go from top-left to bottom-right, we need to process
   // first row and first column at last because they are used as markers.
    for (std::size_t i=row_size-1;i<row_size;--i) {
      for (std::size_t j=col_size-1;j>0;--j) {
        if (matrix[i][0]==0 ||  matrix[0][j]==0) {
          matrix[i][j] = 0;
        }
      }
      if (col0==0) matrix[i][0]=0;
    }

  }
};
```
