class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    if(n<=0) return res;
    vector<string> board(n,string(n,'.'));
    helper(res,board,0,n);
    return res;
  }
private:
  void helper(vector<vector<string>> & res,
              vector<string> & board,
              int row,
              const int n){
    if(row==n){
      res.push_back(board);
    } else {
      // Try put Queen at each cell on this row.
      for(int col=0;col<n;++col){
        if(is_valid(board,row,col,n)){
          board[row][col] = 'Q';
          helper(res,board,row+1,n);//go to next row
          board[row][col] = '.';//revert back
        }
      }
    }
  }
  // Return true/false whether the board is valid if we put a Queen on this cell.
  bool is_valid(const vector<string> & board, const int row, const int col,const int n){
    //check current row
    for(int i=col-1;i>=0;--i){
      if(board[row][i]=='Q') return false;
    }
    //check current column
    for(int i=row-1;i>=0;--i){
      if(board[i][col]=='Q') return false;
    }
    //check to left top corner
    for(int i=row-1,j=col-1;i>=0 && j>=0;--i,--j){
      if(board[i][j]=='Q') return false;
    }
    //check to right top corner
    for(int i=row-1,j=col+1;i>=0 && j<n;--i,++j){
      if(board[i][j]=='Q') return false;
    }
    return true;
  }
};
