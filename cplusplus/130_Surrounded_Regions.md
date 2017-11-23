Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.  

A region is captured by flipping all 'O's into 'X's in that surrounded region.  

For example,  

```
X X X X
X O O X
X X O X
X O X X
```

After running your function, the board should be:

```
X X X X
X X X X
X X X X
X O X X
```

# Solution


### Solution 1, BFS

First, check the four border of the matrix. If there is a element is 'O', alter it and all its neighbor 'O' elements to '#' with BFS.

Now all the original 'O' can be reached from four borders are converted to '#'.

Scane the whole board, for any square whose :

1. value is not '#', convert to 'X'  
2. else means value is '#',  convert to 'O'.  


__One thing that you must be very careful is, we need convert one square's value to be '#' if we are going to put it into bfs_queue.__

For example,

```
00  = > #0  
00      00 
```

Let's say if [0,1] and [1,0] are both in bfs_queue now and they are not marked as '#' and only get marked when pop out of the bfs_queue. Then they will both find a neighbor [2,2] and we will end up push [2,2,] twice into the bfs_queue. When the board is big, this will end up with a lot of recalculations and even infinite loop!


```cpp
class Solution {
    
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return ;
        const int row_size(board.size()), col_size(board[0].size());
        //check first row and last row
        for(int col = 0;col < col_size; ++col){
            if(board[0][col] == 'O') exploreWithBFS(board,0,col);
            if(board[row_size - 1][col] == 'O') exploreWithBFS(board, row_size - 1, col);
        }
        //check first col and last col
        for(int row = 0;row < row_size; ++row){
            if(board[row][0] == 'O') exploreWithBFS(board,row,0);
            if(board[row][col_size - 1] == 'O') exploreWithBFS(board, row, col_size - 1);
        }
        
        for (int row = 0; row < row_size; ++row) {
            for (int col = 0; col < col_size; ++col) {
                if (board[row][col] != '#') {
                    board[row][col] = 'X';
                } else {
                    board[row][col] = 'O';
                }
            }
        }
    }
private:
    void exploreWithBFS(vector<vector<char>>& board, 
                        int row, 
                        int col) {
        static vector< pair<int,int> > steps = {{1,0},{-1,0},{0,1},{0,-1}};
        const int row_size(board.size()), col_size(board[0].size());
        
        if (row < 0 || row >= row_size || col < 0 || col >= col_size) return;
        if (board[row][col] != 'O') return;
        
        board[row][col] = '#';
        queue<pair<int, int>> points;
        points.push(std::make_pair(row, col));
        
        while (!points.empty()) {
            pair<int, int> point = points.front();
            points.pop();
            
            for (const pair<int,int> &step : steps) {
                int next_row = point.first + step.first, next_col = point.second + step.second;
                if (next_row < 0 || next_row >= row_size 
                    || next_col < 0 || next_col >= col_size || board[next_row][next_col] != 'O') {
                    continue;
                } else {
                    board[next_row][next_col] = '#';
                    points.push(std::make_pair(next_row, next_col));
                }
            }
        }
    }
};
```

### Solution 2, DFS

```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
      if (board.empty()) return;
        
      const int row_size(board.size()), col_size(board[0].size());
        
      // first row and last row
      for (int i=0;i<col_size;++i) {
        if (board[0][i] == 'O') exploreWithDFS(board,0,i);
        if (board[row_size-1][i] == 'O') exploreWithDFS(board,row_size-1,i);
      }  
        
      // first col and last col
      for (int i=0;i<row_size;++i) {
        if (board[i][0] == 'O') exploreWithDFS(board,i,0);
        if (board[i][col_size-1] == 'O') exploreWithDFS(board,i,col_size-1);
      }
      
      // if not '#', set it as 'X'
      for (int i=0;i<row_size;++i) {
        for (int j=0;j<col_size;++j) {
          board[i][j] = ( board[i][j] == '#' ? 'O' : 'X'); 
        }
      }
    }
    
    void exploreWithDFS(vector<vector<char>> & board,int row, int col) {
      const int row_size(board.size()), col_size(board[0].size());
        if (row < 0 || row >= row_size || col < 0 || col >= col_size) return;
        if (board[row][col] != 'O') return;
        board[row][col] = '#';
        if(row - 1 >= 0 && board[row - 1][col]=='O') exploreWithDFS(board, row - 1, col);
        if(row + 1 < row_size && board[row+1][col]=='O') exploreWithDFS(board, row + 1,col);
        if(col - 1 >= 0 && board[row][col-1]=='O') exploreWithDFS(board, row, col - 1);
        if(col + 1 < col_size && board[row][col+1]=='O') exploreWithDFS(board, row, col + 1);
    }
};
```
