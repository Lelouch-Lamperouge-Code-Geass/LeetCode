class Solution {
public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    if (dungeon.empty()) return 1;
    const std::size_t row_size(dungeon.size()),col_size(dungeon[0].size());
    // record the minimal hp when enter the room
    std::vector< std::vector<int> > min_hp(row_size+1,std::vector<int>(col_size+1,INT_MAX));
    min_hp[row_size-1][col_size] =  min_hp[row_size][col_size-1] = 1;
    // since we use size_t here, need hanlde 0-1 scenario
    for (std::size_t i = row_size-1;i>=0&&i<row_size;--i) {
      for (std::size_t j = col_size-1;j>=0&&j<col_size;--j) {
        min_hp[i][j] = std::max(1,std::min(min_hp[i+1][j],min_hp[i][j+1]) - dungeon[i][j]);
      }
    }
    return min_hp[0][0];
  }
};
