You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

```
1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
```

The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

# Solution

 The time complexity for BFS/DFS is O(|V|+|E|), not O(|V||E|). In this problem, every vertex has up to 4 edges (left, right, up, down), so |E| ~ 4|V|. Thus, you have overall O(|V|) = O(mn) for a BFS. This has been proven for all sparse graphs like this problem. Now, we do a BFS for each building, so the overall complexity is O(#buildings*(mn)). In worst case, every vertex is a building. So the number of buildings is also upper bounded by O(mn), and thus you have O((mn)(mn)) = O(m^2n^2). This is a very loose bound since when every vertex is a building, we don't even need to do a BFS (nowhere to go).


###  StefanPochmann's solution

I also tested the other three C++ solutions posted so far, they took 340-1812 ms. I think mine is faster because I don't use a fresh "visited" for each BFS. Instead, I walk only onto the cells that were reachable from all previous buildings. From the first building I only walk onto cells where grid is 0, and make them -1. From the second building I only walk onto cells where grid is -1, and I make them -2. And so on.

```cpp
int shortestDistance(vector<vector<int>> grid) {
    int m = grid.size(), n = grid[0].size();
    auto total = grid;
    int walk = 0, mindist, delta[] = {0, 1, 0, -1, 0};
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (grid[i][j] == 1) {
                mindist = -1;
                auto dist = grid;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                while (q.size()) {
                    auto ij = q.front();
                    q.pop();
                    for (int d=0; d<4; ++d) {
                        int i = ij.first + delta[d];
                        int j = ij.second + delta[d+1];
                        if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == walk) {
                            grid[i][j]--;
                            dist[i][j] = dist[ij.first][ij.second] + 1;
                            total[i][j] += dist[i][j] - 1;
                            q.emplace(i, j);
                            if (mindist < 0 || mindist > total[i][j])
                                mindist = total[i][j];
                        }
                    }
                }
                walk--;
            }
        }
    }
    return mindist;
}
```


### my solution

Traverse the matrix. For each building, use BFS to compute the shortest distance from each building to
empty space. After we do this for all the buildings, we can get the sum of shortest distance
from every '0' to all reachable buildings. This value is stored
in ```final_distance[][]```. For example, if ```grid[2][2] == 0```, ```final_distance[2][2]``` is the sum of shortest distance from this block to all reachable buildings.

We also count how many building each '0' can be reached. It is stored in ```reach[][]```. This can be done during the BFS. We also need to count how many total buildings are there in the matrix, which is stored in 'total_building'.

Finally, we can traverse the ```final_distance[][]``` matrix to get the point having shortest distance to all buildings. ```O(m*n)```.

The total time complexity will be ```O(m^2*n^2)```, which is quite high!. 

```cpp
class Solution {
private:
    void bfsFromBuilding(const vector<vector<int>>& grid,
                         vector<vector<int>> &total_distance,
                         vector<vector<int>> &distance,
                         vector<vector<bool>> &visited,
                         vector<vector<int>>  &reach,
                         int row, 
                         int col) {
        static vector<pair<int, int>> moves = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}  
        };
        const int row_size = distance.size(), col_size = distance[0].size();
        queue<pair<int, int>> nodes;
        nodes.push(make_pair(row, col));
        visited[row][col] = true;
        while (!nodes.empty()) {
            pair<int, int> cur_node = nodes.front();
            nodes.pop();
            for (const auto &move : moves) {
                int next_row = cur_node.first + move.first;
                int next_col = cur_node.second + move.second;
                
                // We need make sure range is valid.
                // And we also only push node into queue
                // when the expecting distance is smaller.
                // This is an effective way to avoid re-visit
                // as well we unnecessary visit.
                if (next_row >= 0 && next_row < row_size
                    && next_col >= 0 && next_col < col_size
                    && !visited[next_row][next_col]
                    && grid[next_row][next_col] == 0) {
                    visited[next_row][next_col] = true;
                    nodes.push(make_pair(next_row, next_col));
                    distance[next_row][next_col] = distance[cur_node.first][cur_node.second] + 1;
                    total_distance[next_row][next_col] += distance[next_row][next_col];
                    ++ reach[next_row][next_col];
                }
            }
        }
    }
public:
    int shortestDistance(vector<vector<int>>& grid) {
        const int row_size = grid.size(), col_size = grid[0].size();
        
        vector<vector<int>> total_distance(row_size, vector<int>(col_size, 0));
        vector<vector<int>> distance(row_size, vector<int>(col_size, 0));
        vector<vector<int>> reach(row_size, vector<int>(col_size, 0));

        int total_building(0);
        for (int row = 0; row < row_size; ++row) {
            for (int col = 0; col < col_size; ++col) {
                if (grid[row][col] == 1) {
                    ++ total_building;
                    vector<vector<int>> cur_distance = distance;
                    vector<vector<bool>> visited(row_size, vector<bool>(col_size, false));
                    bfsFromBuilding(grid, total_distance, cur_distance, visited, reach, row, col);
                }
            }
        }
        
        int reval(INT_MAX);
        for (int row = 0; row < row_size; ++row) {
            for (int col = 0; col < col_size; ++col) {
                if (grid[row][col] == 0 && reach[row][col] == total_building ) {
                    reval = std::min(reval, total_distance[row][col]);
                }
            }
        }
        
        return reval == INT_MAX ? -1 : reval;
    }
};
```
