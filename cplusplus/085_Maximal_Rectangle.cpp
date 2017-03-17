/*
The DP solution proceeds row by row, starting from the first row. 
Let the maximal rectangle area at row i and column j be computed by [right(i,j) - left(i,j)]*height(i,j).
All the 3 variables left, right, and height can be determined by the information from previous row, 
and also information from the current row. So it can be regarded as a DP solution. The transition equations are:

left(i,j) = max(left(i-1,j), cur_left), cur_left can be determined from the current row
right(i,j) = min(right(i-1,j), cur_right), cur_right can be determined from the current row
height(i,j) = height(i-1,j) + 1, if matrix[i][j]=='1';
height(i,j) = 0, if matrix[i][j]=='0'
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
      for (int col=0;col<col_size;++col) {
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
/*
solution 2
*/
class Solution {
public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.empty()) return 0;
    int max_rec(0);
    const int M(matrix.size()),N(matrix[0].size());
    vector<int> dp(matrix[0].size(),0);
    for(int i=0;i<M;++i){
      for(int j=0;j<N;++j){
        dp[j] = matrix[i][j]=='0'? 0 : dp[j] + 1;
      }
      max_rec = std::max(max_rec,largestRectangleArea(dp));
    }
    return max_rec;
  }
private:
  int largestRectangleArea(vector<int>& heights) {
    heights.push_back(0);
    const std::size_t heights_size(heights.size());
    int max_area(0);
    vector<std::size_t> non_descend_heights;
    for (std::size_t i=0;i<heights_size;++i) {
      while (!non_descend_heights.empty() && heights[non_descend_heights.back()]>heights[i]) {
        int height = heights[non_descend_heights.back()];
        non_descend_heights.pop_back();
        int width = non_descend_heights.empty()? i : i-non_descend_heights.back()-1;
        max_area = std::max(max_area,height*width);
      }
      non_descend_heights.push_back(i);
    }
    heights.pop_back(); // revert back
    return max_area;
  }
};
