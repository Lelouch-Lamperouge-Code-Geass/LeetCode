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
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        const std::size_t row_size(grid.size()), col_size(grid[0].size());
        int reval(0);
        for (std::size_t row = 0; row < row_size; ++ row) {
            for (std::size_t col = 0; col < col_size; ++col) {
                if (grid[row][col] == '1') {
                    findWithBFS(grid, row, col);
                    ++ reval;
                }
            }
        }
        return reval;
    }
private:
    void findWithBFS(vector<vector<char>>& grid, std::size_t row, std::size_t col) {
        const std::size_t row_size(grid.size()), col_size(grid[0].size());
        
        if (row < row_size && col < col_size && grid[row][col] == '1') {
            std::queue<std::pair<std::size_t, std::size_t>> coordinates;
            grid[row][col] = '0';
            coordinates.emplace(std::make_pair(row, col));
            
            while (!coordinates.empty()) {
                const std::size_t cur_row = coordinates.front().first,
                    cur_col = coordinates.front().second;
                coordinates.pop();
                if (cur_row > 0 && grid[cur_row - 1][cur_col] == '1') {
                    grid[cur_row - 1][cur_col] = '0';
                    coordinates.emplace(std::make_pair(cur_row - 1, cur_col));
                }
                
                if (cur_row + 1 < row_size && grid[cur_row + 1][cur_col] == '1') {
                    grid[cur_row + 1][cur_col] = '0';
                    coordinates.emplace(std::make_pair(cur_row + 1, cur_col));
                }
                
                if (cur_col > 0 && grid[cur_row][cur_col - 1] == '1') {
                    grid[cur_row][cur_col - 1] = '0';
                    coordinates.emplace(std::make_pair(cur_row, cur_col - 1));
                }
                
                if (cur_col + 1 < col_size && grid[cur_row][cur_col + 1] == '1') {
                    grid[cur_row][cur_col + 1] = '0';
                    coordinates.emplace(std::make_pair(cur_row, cur_col + 1));
                }
            }
        } 
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

