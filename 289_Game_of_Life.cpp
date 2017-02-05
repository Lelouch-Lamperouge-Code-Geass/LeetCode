// https://segmentfault.com/a/1190000003819277

/* Solution 1 : Space Complexity is O(MN), the most intuitive solution*/
class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;
    const int row_size(board.size()), col_size(board[0].size());
    vector< vector<int> > stats(row_size,vector<int>(col_size,0));
    for (int i=0;i<row_size;++i) {
      for (int j=0;j<col_size;++j) {
        int start_row = std::max(0,i-1), start_col =  std::max(0,j-1),
          end_row = std::min(row_size-1,i+1), end_col = std::min(col_size-1,j+1);
        for (int q=start_row;q<=end_row;++q) {
          for (int p=start_col;p<=end_col;++p) {
            if (q==i&&p==j) continue;
            stats[i][j] += board[q][p];
          }
        }
      }
    }

    for (int i=0;i<row_size;++i) {
      for (int j=0;j<col_size;++j) {
        if (stats[i][j]<2 || stats[i][j]>3) board[i][j] = 0;
        else if (stats[i][j]==3) board[i][j] = 1;
        else {} // no change
      }
    }
  }
};

/* Solution 2: optimize based on solution 1, in-place solution */
class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    if(board.empty()) return;
    const int M(board.size()),N(board[0].size());
    for(int row=0;row<M;++row){
      for(int col=0;col<N;++col){
        int count(0);
        //calculate live neighbors
        for(int i=std::max(0,row-1);i<=std::min(M-1,row+1);++i){
          for(int j=std::max(0,col-1);j<=std::min(N-1,col+1);++j){
            if(i==row && j==col) continue;
            count += board[i][j] & 1;
          }
        }
        if(count==3 || (board[row][col]&&count==2))
          board[row][col]|=2;
      }
    }
    for (std::size_t row=0;row<M;++row){
      for (std::size_t col=0;col<N;++col){
        board[row][col] >>= 1;
      }
    }
  }
};


class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        if (board.empty()) return;
        const std::size_t row_size(board.size()), col_size(board[0].size());
        for (std::size_t row = 0; row < row_size; ++ row) {
            for (std::size_t col = 0; col < col_size; ++ col) {
                std::size_t start_row = row > 0 ? row - 1 : 0;
                std::size_t end_row = row < row_size - 1 ? row + 1 : row;
                std::size_t start_col = col > 0 ? col - 1 : 0;
                std::size_t end_col = col < col_size - 1 ? col + 1 : col;
  
                int live_neighbor(0);
                for (std::size_t i = start_row; i <= end_row; ++i) {
                    for (std::size_t j = start_col; j <= end_col; ++j) {
                        if (i == row && j == col) {
                            continue;
                        } else {
                            live_neighbor += board[i][j] & 1;
                        }
                    }
                }
                
                if (live_neighbor == 3 || (live_neighbor == 2 && board[row][col]==1) ) {
                    board[row][col] |= 2 ;
                }
            }
        }
        for (std::size_t row = 0; row < row_size; ++ row) {
            for (std::size_t col = 0; col < col_size; ++ col) {
                board[row][col] >>= 1;
            }
        }
    }
};


