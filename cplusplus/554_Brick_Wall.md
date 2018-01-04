There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.

The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.

If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.

__You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.__

##### Example:

![alt](https://leetcode.com/static/images/problemset/brick_wall.png)

```
Input: 
[[1,2,2,1],
 [3,1,2],
 [1,3,2],
 [2,4],
 [3,1,2],
 [1,3,1,1]]
Output: 2
```

##### Note:

1. The width sum of bricks in different rows are the same and won't exceed INT_MAX.
2. The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.

# Solution

##### My first naive solution, get MLE

```cpp
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        const int width = std::accumulate(wall[0].begin(), wall[0].end(), 0);
        
        vector<int> bricks(width + 1, 0);
        
        for (const vector<int> &brick_layer : wall) {
            // We assume that current layer has no vertical line at first.
            vector<int> fill(width + 1, 1);
            int cur_width(0);
            for (int brick_width : brick_layer) {
                cur_width += brick_width;
                
                // Be careful when reach edge, it should always be 1
                if (cur_width != width) fill[cur_width] = 0;
            }
            
            for (int i = 0; i <= width; ++i) {
                bricks[i] += fill[i];
            }
        }
        
        return *std::min_element(bricks.begin(), bricks.end());
    }
};
```

### A better solution

For each potential cut position - which is at the edge of any brick, I am counting the number of brick edges for all rows. Note that we need to use hash map to only track potential (not all) cuts. If bricks are very wide, you'll get MLE if you store all cut positions.

```cpp
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        const int row_size(wall.size());
        int least_bricks(row_size);
        std::unordered_map<int, int> edges;
        for (const vector<int> &row : wall) {
            int cur_width(0);
            
            // Here i + 1 < n make sure that we ignore the right edge of last brick
            for (std::size_t i = 0, n = row.size(); i + 1 < n; ++i) {
                cur_width += row[i];
                ++ edges[cur_width];
                least_bricks = std::min(least_bricks, row_size - edges[cur_width]);
            }
        }
        
        return least_bricks;
    }
};
```
