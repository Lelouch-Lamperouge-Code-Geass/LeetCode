Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

```
11110
11010
11000
00000
```

Answer: 1

Example 2:

```
11000
11000
00100
00011
```

Answer: 3

# Solution


##### Solution one : BFS

```cpp
class Solution {
private:
    void checkWithBFS(vector<vector<char>>& grid, int row, int col) {
        static const vector<pair<int, int>> moves = {{1,0},{-1, 0}, {0, 1}, {0, -1}};
        const int row_size = grid.size(), col_size = grid[0].size();
        
        grid[row][col] = '0';
        queue<pair<int, int>> cells;
        cells.push(make_pair(row, col));
        while (!cells.empty()) {
            pair<int, int> cur_cell = cells.front();
            cells.pop();
            
            for (const pair<int, int> &move : moves) {
                int next_row = cur_cell.first + move.first, 
                    next_col = cur_cell.second + move.second;
                // Check boundary
                if (next_row < 0 || next_row >= row_size 
                    || next_col < 0 || next_col >= col_size) continue;
                // Must be '1'
                if (grid[next_row][next_col] == '0') continue;
                
                // We must change the char to be '0' before push the the queue.
                // Otherwise it is possible that one cell get pushed into the queue
                // multiple times since it is a neighbor of mutiple cells.
                grid[next_row][next_col] = '0';
                
                cells.push(make_pair(next_row, next_col));
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int reval(0);
        for (int row = 0, row_size = grid.size(); row < row_size; ++row) {
            for (int col = 0, col_size = grid[0].size(); col < col_size; ++col) {
                if (grid[row][col] == '1') {
                    checkWithBFS(grid, row, col); 
                    ++ reval;
                }
            }
        }
        return reval;
    }
};
```

##### Solution two : DFS

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        const std::size_t row_size(grid.size()), col_size(grid[0].size());
        
        int reval(0);
        for (int row=0;row<row_size;++row) {
            for (int col=0;col<col_size;++col) {
                if (grid[row][col] == '1') {
                   ++ reval;
                   searchWithDFS(grid,row,col);
                }        
            }
        }
        
        // Should recover original input
        revertBack(grid);
        
        return reval;
    }
private:
    void revertBack(vector<vector<char>> &grid) {
        const std::size_t row_size(grid.size()), col_size(grid[0].size());
        for (std::size_t row; row < row_size; ++ row) {
            for (std::size_t col; col < col_size; ++ col) {
                if ('x' == grid[row][col]) {
                    grid[row][col] = '1';
                }
            }
        }
    }
    void searchWithDFS(vector<vector<char>>& grid,
                      const std::size_t row,
                      const std::size_t col) {
        const int row_size(grid.size()),col_size(grid[0].size());
        if(row<0 || col<0 || row>=row_size || col>=col_size) return;
        if(grid[row][col] != '1') return;
        grid[row][col] = 'x';
        searchWithDFS(grid,row-1,col);
        searchWithDFS(grid,row+1,col);
        searchWithDFS(grid,row,col-1);
        searchWithDFS(grid,row,col+1);
    }
};
```

##### Solution Three : Union Find

