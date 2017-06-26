// 1. Two Queue and add all the Pacific border to one queue; Atlantic border to another queue.
// 2. Keep a visited matrix for each queue. In the end, add the cell visited by two queue to the result.
//    BFS: Water flood from ocean to the cell. Since water can only flow from high/equal cell to low cell,
//    add the neighboor cell with height larger or equal to current cell to the queue and mark as visited.
class Solution {
private:
  typedef std::list<std::pair<int,int>> CoordinatesList;
  std::vector< std::pair<int,int> > moves = {
    {0,1}, {0,-1}, {1,0}, {-1,0}
  };
  void initialize_bfs_list(CoordinatesList & pacific_list,
                           CoordinatesList & atlantic_list,
                           vector<vector<bool>> & pacific_visited,
                           vector<vector<bool>> & atlantic_visited,
                           const std::size_t row_size,
                           const std::size_t col_size) {
    // Horizontal border
    for (std::size_t col = 0; col < col_size; ++col) {
      pacific_list.push_back(std::make_pair(0,col));
      pacific_visited[0][col] = true;
      atlantic_list.push_back(std::make_pair(row_size - 1,col));
      atlantic_visited[row_size - 1][col] = true;
    }
    // Vertical border
    for (std::size_t row = 0; row < row_size; ++row) {
      pacific_list.push_back(std::make_pair(row, 0));
      pacific_visited[row][0] = true;
      atlantic_list.push_back(std::make_pair(row, col_size - 1));
      atlantic_visited[row][col_size - 1] = true;
    }
  }

  void bfs_seek(const vector<vector<int>> & matrix,
                }
    }

  return reval;
}
};
