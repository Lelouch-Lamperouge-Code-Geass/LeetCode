class Solution {
private:
  struct Cell {
    Cell(int row, int col, int height) : m_row(row), m_col(col), m_height(height) {

    }
    int m_row;
    int m_col;
    int m_height;
  };

  struct CellCompare {
    bool operator()(const Cell & left, const Cell & right){
      return left.m_height > right.m_height;
    }
  };

  typedef std::priority_queue<Cell, std::vector<Cell>, CellCompare> MinHeightCellHeap;

  void AddBorderToMinHeightHeap(const vector<vector<int>>& heightMap,
                                [col] = true;
                                reval += std::max(cur_cell.m_height - heightMap[row][col], 0);
                                min_heap.push(Cell(row, col, std::max(cur_cell.m_height, heightMap[row][col])));
                                }
    }

  min_heap.pop();
}
}

public:

int trapRainWater(vector<vector<int>>& heightMap) {
  if (heightMap.empty()) return 0;
  const int row_size(heightMap.size()), col_size(heightMap[0].size());
  MinHeightCellHeap min_heap;
  vector<vector<bool>> visited(row_size, vector<bool>(col_size, false));
  AddBorderToMinHeightHeap(heightMap, min_heap, visited);
  int reval(0);
  SeekWithBFS(heightMap, min_heap, visited, reval);
  return reval;
}
};
