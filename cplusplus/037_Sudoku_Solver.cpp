/*Solution 1*/
// https://
// discuss.leetcode.com/topic/7195/sharing-my-2ms-c-solution-with-comments-and-explanations

/* Solution 2 */

class Solution {
 public:
  void solveSudoku(vector<vector<char>>& board) { TrySolve(board, 0, 0); }

 private:
  bool TrySolve(vector<vector<char>>& board, int row, int col) {
    if (row == 9) return true;
    if (board[row][col] == '.') {
      for (char c = '1'; c <= '9'; ++c) {
        if (IsValid(board, row, col, c)) {
          board[row][col] = c;
          if (col == 8 && TrySolve(board, row + 1, 0) ||
              col < 8 && TrySolve(board, row, col + 1))
            return true;
          board[row][col] = '.';
        }
      }
      return false;
    } else {
      return (col == 8 && TrySolve(board, row + 1, 0)) ||
             col < 8 && TrySolve(board, row, col + 1);
    }
  }

  bool IsValid(const vector<vector<char>>& board, const int row, const int col,
               const char cur_val) {
    // check current row
    for (int i = 0; i < 9; i++)
      if (board[row][i] == cur_val) return false;
    // check current col
    for (int i = 0; i < 9; i++)
      if (board[i][col] == cur_val) return false;
    // check current block
    const int start_i(row / 3 * 3), start_j(col / 3 * 3);
    for (int i = start_i; i < start_i + 3; ++i)
      for (int j = start_j; j < start_j + 3; ++j)
        if (board[i][j] == cur_val) return false;
    return true;
  }
};

/* Solution 3, almost same as solution 2 */
class Solution {
 public:
  void solveSudoku(vector<vector<char>>& board) { solve(board); }

 private:
  bool solve(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          for (char c = '1'; c <= '9'; c++) {
            if (is_valid(board, i, j, c)) {
              board[i][j] = c;
              if (solve(board))
                return true;
              else
                board[i][j] = '.';
            }
          }
          return false;
        }
      }
    }
    return true;
  }
  bool is_valid(const vector<vector<char>>& board, const int row, const int col,
                const char cur_val) {
    // check current row
    for (int i = 0; i < 9; i++)
      if (board[row][i] == cur_val) return false;
    // check current col
    for (int i = 0; i < 9; i++)
      if (board[i][col] == cur_val) return false;
    // check current block
    const int start_i(row / 3 * 3), start_j(col / 3 * 3);
    for (int i = start_i; i < start_i + 3; i++)
      for (int j = start_j; j < start_j + 3; j++)
        if (board[i][j] == cur_val) return false;
    return true;
  }
};
