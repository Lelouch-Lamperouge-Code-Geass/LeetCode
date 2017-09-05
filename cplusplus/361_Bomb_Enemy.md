Given a 2D grid, each cell is either a wall 'Y', an enemy 'X' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:

For the given grid

```
0 X 0 0
X 0 Y X
0 X 0 0
```
return 3. (Placing a bomb at (1,1) kills 3 enemies)
  
# Solution

Walk through the matrix. At the start of each non-wall-streak (row-wise or column-wise), count the number of hits in that streak and remember it. O(mn) time, O(n) space.
  
```cpp

int maxKilledEnemies(vector<vector<char>>& grid) {
  int row_size = grid.size(), col_size = row_size != 0 ? grid[0].size() : 0;
  int result = 0, rowhits, colhits[n];
  for (int row = 0; row < row_size; ++ row) {
    for (int col = 0; col < col_size; ++ col) {
      // Going rightward and calculate how many hits on this row.
      // We only need to update the row hits when its left box is a wall.
      // There is basically a wall on the left when col == 0.
      if (col == 0 || grid[row][col-1] == 'W') {
        rowhits = 0;
        for (int k = col; k < col_size && grid[row][k] != 'W'; ++k)
          rowhits += (grid[row][k] == 'E'? 1 : 0);
      }

      // Going downward and calculate how many hits on this column.
      // We only need to update the column hits when its above box is a wall.
      // There is basically a wall above when row == 0.
      if (row == 0 || grid[row-1][col] == 'W') {
        colhits[col] = 0;
        for (int k = i; k < row_size && grid[k][col] != 'W'; ++k)
          colhits[col] += ( grid[k][col] == 'E'? 1 : 0 );
      }
      
      if (grid[row][col] == '0') { // Can place bomb here
        result = max(result, rowhits + colhits[col]);
      }
    }
  }
  return result;
}
```
