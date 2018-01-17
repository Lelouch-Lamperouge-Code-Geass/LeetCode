You are given a m x n 2D grid initialized with these three possible values.  

-1 - A wall or an obstacle.  
0 - A gate.  
INF - Infinity means an empty room. 

We use the value 2^31 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.  
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
For example, given the 2D grid:  

```
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
```

After running your function, the 2D grid should be:
```
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
```

# Solution

### Solution one , BFS
Push all gates into queue first. Then for each gate update its neighbor cells and push them to the queue.  
Repeating above steps until there is nothing left in the queue.

```cpp
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty()) return;
        static std::vector<std::pair<int,int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        const std::size_t row_size(rooms.size()), col_size(rooms[0].size());
        std::queue< std::pair<std::size_t, std::size_t> > bfs_queue;
        for (std::size_t i = 0; i < row_size; ++i) {
            for (std::size_t j = 0; j < col_size; ++j) {
                if (0 == rooms[i][j]) {
                    bfs_queue.emplace(i, j);
                }
            }
        }
        
        while (!bfs_queue.empty()) {
            std::size_t r = bfs_queue.front().first, c = bfs_queue.front().second;
            bfs_queue.pop();
            for (const std::pair<int,int> &direction : directions) {
                std::size_t row = r + direction.first;
                std::size_t col = c + direction.second;
                if (row < row_size 
                    && col < col_size 
                    && rooms[row][col] > rooms[r][c] + 1) {
                    // rooms[row][col] > rooms[r][c] + 1 guarantees that 
                    // we won't visit the box we already visited
                    // as well as avoid unnecessary re-calculations
                    rooms[row][col]  = rooms[r][c] + 1;
                    bfs_queue.emplace(row, col);
                }
            }
        }
    }
};
```

### Solution two, DFS


```cpp
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty()) return;
        const std::size_t row_size(rooms.size()), col_size(rooms[0].size());
        for (std::size_t i = 0; i < row_size; ++i) {
            for (std::size_t j = 0; j < col_size; ++j) {
                if (0 == rooms[i][j]) {
                    DFS(rooms,i, j, 0);
                }
            }
        }
    }
private:
    void DFS(vector<vector<int>> &rooms, 
             std::size_t row, 
             std::size_t col,
             int distance) {
        const std::size_t row_size(rooms.size()), col_size(rooms[0].size());
        // Note here since gate is 0 and obstacle is -1,
        // their values determine that we will be blocked once we meet them.
        if (row >= row_size || col >= col_size || rooms[row][col] <= distance) return;
        rooms[row][col] = distance;
        DFS(rooms, row - 1, col, distance + 1);
        DFS(rooms, row + 1, col, distance + 1);
        DFS(rooms, row, col - 1, distance + 1);
        DFS(rooms, row, col + 1, distance + 1);
    }
};
```

A different style.

```cpp
class Solution {
private:
    static  int EMPTY_ROOM;
    static  int GATE;
    static  int OBSTACLE;
    void travelWithDFS(vector<vector<int>> &rooms,
                       int row,
                       int col,
                       const int distance) {
        
        static vector<pair<int,int>> moves = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
        const int row_size = rooms.size(), col_size = rooms[0].size();
        rooms[row][col] = std::min(rooms[row][col], distance);
        for (const pair<int, int> &move : moves) {
            int next_row = row + move.first, next_col = col + move.second;
            if (next_row < 0 || next_row >= row_size
               || next_col < 0 || next_col >= col_size) continue;
            if (rooms[next_row][next_col] == OBSTACLE
               || rooms[next_row][next_col] == GATE) continue;
            if (rooms[next_row][next_col] <= distance + 1) continue;
            travelWithDFS(rooms, next_row, next_col, distance + 1);
        }
    }
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        for (int row = 0, row_size = rooms.size(); row < row_size; ++row) {
            for (int col = 0, col_size = rooms[0].size(); col < col_size; ++col) {
                if (rooms[row][col] == GATE) {
                    travelWithDFS(rooms, row, col, 0);
                }
            }
        }
    }
};

int Solution::EMPTY_ROOM = INT_MAX;
int Solution::GATE = 0;
int Solution::OBSTACLE = -1;
```
