class Solution {
public:
  void rotate(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    std::reverse(matrix.begin(),matrix.end());
    const std::size_t n(matrix.size());
    for (std::size_t i=0;i<n;++i) {
      for (std::size_t j=i+1;j<n;++j) {
        std::swap(matrix[i][j],matrix[j][i]);
      }
    }
  }
};
