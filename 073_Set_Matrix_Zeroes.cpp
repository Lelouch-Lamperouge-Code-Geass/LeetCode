/*
Using O(mn) space is to naive. Will not discuss that solution here.
This solution is uses O(m + n) space.
*/
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

    for (int i=row_size-1;i<row_size;--i) {
      for (int j=col_size-1;j<col_size;--j) {
        if(zero_row[i] || zero_col[j])
          matrix[i][j] = 0;
      }
    }
  }
};

/*
This solution use O(1).
My idea is simple: store states of each row in the first of that row, and store states of each column in the first of that column. Because the state of row0 and the state of column0 would occupy the same cell, I let it be the state of row0, and use another variable "col0" for column0. In the first phase, use matrix elements to set states in a top-down way. In the second phase, use states to set matrix elements in a bottom-up way.
Notice that the first column is handled different here.
*/

class Solution {
public:
  void setZeroes(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    const std::size_t row_size(matrix.size()),col_size(matrix[0].size());
    int col0 = 1; // represents whether column 0 should be zeroes
    for (std::size_t i=0;i<row_size;++i) {
      if (matrix[i][0]==0) col0 = 0;
      for (std::size_t j=1;j<col_size;++j) {
        if (matrix[i][j]==0) {
          matrix[i][0] = matrix[0][j] = 0;
        }
      }
    }

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
