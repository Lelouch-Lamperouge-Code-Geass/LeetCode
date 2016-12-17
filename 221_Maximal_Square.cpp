class Solution {
public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    const int row_size(matrix.size()), col_size(matrix[0].size());
    vector< vector<int> > max_square_len(row_size+1,vector<int>(col_size+1,0));
    int max_len(0);
    for (int i=1;i<=row_size;++i) {
      for (int j=1;j<=col_size;++j) {
        if (matrix[i-1][j-1]=='0') {
          max_square_len[i][j] = 0;
        } else {
          max_square_len[i][j] = std::min(max_square_len[i-1][j-1]
                                          ,std::min(max_square_len[i-1][j],max_square_len[i][j-1]) ) + 1;
          max_len = std::max(max_len,max_square_len[i][j]);
        }
      }
    }
    return max_len * max_len;
  }
};
