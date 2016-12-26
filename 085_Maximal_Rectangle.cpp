/*
height counts the number of successive '1's above (plus the current one). 
The value of left & right means the boundaries of the rectangle which contains the current point with a height of value height.
*/
class Solution {
public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.empty()) return 0;
    const int row_size(matrix.size()), col_size(matrix[0].size());
    vector<int> left(col_size,0),right(col_size,col_size-1),height(col_size,0);

    int max_area(0);
    for (int row=0;row<row_size;++row) {
      // calculate height on each cell
      for (int col=0;col<col_size;++col) {
        if (matrix[row][col] == '1') {
          ++ height[col];
        } else {
          height[col] = 0;
        }
      }

      // calculate left boundary has height for that index, from left to right
      int left_most(0);
      for (int col=1;col<col_size;++col) {
        if (matrix[row][col] == '1') {
          left[col] = std::max(left_most,left[col]);
        } else {
          left[col] = 0;
          left_most = col + 1;
        }
      }

      // calculate right boundary has height for that index, from right to left
      int right_most(col_size-1);
      for (int col=col_size-1;col>=0;--col) {
        if (matrix[row][col] == '1') {
          right[col] = std::min(right[col],right_most);
        } else {
          right[col] = col_size-1;
          right_most = col-1;
        }
      }


      for (int col=0;col<col_size;++col) {
        max_area = std::max(max_area,(right[col]-left[col]+1) * height[col] );
      }
    }

    return max_area;
  }
};
