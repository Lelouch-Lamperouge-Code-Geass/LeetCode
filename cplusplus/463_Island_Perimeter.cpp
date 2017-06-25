// Solution one, 222 ms
class Solution {
public:
  int islandPerimeter(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    std::size_t reval(0);
    const std::size_t grid_row_size(grid.size());
    const std::size_t grid_col_size(grid[0].size());

    for (std::size_t row(0); row < grid_row_size; ++row) {
      for (std::size_t col(0); col < grid_col_size; ++col) {
        if (grid[row][col] == 1) {
          if (row == 0 || grid[row-1][col] == 0) ++ reval;
          if (row + 1 ==  grid_row_size || grid[row+1][col] == 0) ++ reval;
          if (col == 0 || grid[row][col-1] == 0) ++ reval;
          if (col + 1 ==  grid_col_size || grid[row][col+1] == 0) ++ reval;
        }
      }
    }

    return reval;
  }
};

// Solution 2
// Every adjacent islands made two sides disappeared.
// +--+     +--+                   +--+--+
// |  |  +  |  |          ->       |     |
// +--+     +--+                   +--+--+
// So the pattern is islands * 4 - neighbours * 2

class Solution {
public:
  int islandPerimeter(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    std::size_t square_count(0), adjacent_pair(0);
    const std::size_t grid_row_size(grid.size());
    const std::size_t grid_col_size(grid[0].size());
    for (std::size_t row = 0; row < grid_row_size; ++ row) {
      for (std::size_t col = 0; col < grid_col_size; ++ col) {
        if (grid[row][col] == 1) {
          ++ square_count;

          // Check right
          if (col+1 < grid_col_size && grid[row][col+1] == 1) ++ adjacent_pair;
          // Check down
          if (row+1 < grid_row_size && grid[row+1][col] == 1) ++ adjacent_pair;
        }
      }
    }

    return 4 * square_count - 2 * adjacent_pair;
  }
};


