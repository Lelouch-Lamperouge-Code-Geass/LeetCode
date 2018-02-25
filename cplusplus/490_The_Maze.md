There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

##### Example 1

```
Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

```

![alt](https://leetcode.com/static/images/problemset/maze_1_example_1.png)

##### Example 2

Input 1: a maze represented by a 2D array

```
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: false
Explanation: There is no way for the ball to stop at the destination.

```

![alt](https://leetcode.com/static/images/problemset/maze_1_example_2.png )

##### Note:

1. There is only one ball and one destination in the maze.
2. Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
3. The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
4. The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

# Solution

We begin from the start position and can roll in four directions at each "stoppable position" which is the stopped position on each rolling process. The problem is asking whether we can stop at the destination position, which means that the destination point should be a "stoppable position" too. 

We can use BFS/DFS to solve this problem.


### Solution one with BFS

We begin with start position and keep rolling and adding "stoppable positions" into the bfs-queue. We need to mark these positions before we put them into the bfs-queue.

```cpp
class Solution {
private:
    std::string getHash(int left, int right) {
        ostringstream oss;
        oss << left << '-' << right;
        return oss.str();
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        static vector<pair<int,int>> directions = {{1,0},{0,1},{-1,0},{0,-1}};
        if (maze.empty()) return false;
        const int row_size(maze.size()), col_size(maze[0].size());
        unordered_set<std::string> visited;
        queue<pair<int, int>> nodes;
        nodes.push(make_pair(start[0], start[1]));
        visited.insert(getHash(start[0], start[1]));
        
        while (!nodes.empty()) {
            int x = nodes.front().first, y = nodes.front().second;
            nodes.pop();
            if (x == destination[0] && y == destination[1]) return true;
            for (const pair<int, int> &dir : directions) {
                int xx(x), yy(y);
                
                // Begin rolling
                while (xx >= 0 && xx < row_size 
                    && yy >= 0 && yy < col_size 
                    && maze[xx][yy] == 0) {
                    xx += dir.first;
                    yy += dir.second;
                }
                
                // Crossed border, go one step back
                xx -= dir.first;
                yy -= dir.second;
                    
                if (visited.count(getHash(xx, yy)) == 0) {
                    visited.insert(getHash(xx, yy));
                    nodes.push(make_pair(xx, yy));
                }    
            }
            
        }
        
        return false;
    }
};
```
