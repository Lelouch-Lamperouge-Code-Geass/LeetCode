// Solution one
class Solution {
public:
  int countBattleships(vector<vector<char>>& board) {
    if (board.empty()) return 0;
    const std::size_t board_row_size(board.size());
    const std::size_t board_col_size(board[0].size());

    std::size_t x_count(0), neighbor_count(0);

    for (std::size_t row = 0; row < board_row_size; ++ row) {
      for (std::size_t col = 0; col < board_col_size; ++ col) {
        if (board[row][col] == 'X') {
          ++ x_count;
          // Check right
          if (col+1 < board_col_size && board[row][col+1] == 'X') ++ neighbor_count;

          // Check down
          if (row+1 < board_row_size && board[row+1][col] == 'X') ++ neighbor_count;
        }
      }
    }

    return x_count - neighbor_count;
  }
};

// Solution two
class Solution {
public:
  int countBattleships(vector<vector<char>>& board) {
    if (board.empty()) return 0;
    const std::size_t board_row_size(board.size());
    const std::size_t board_col_size(board[0].size());

    std::size_t reval(0);

    for (std::size_t row = 0; row < board_row_size; ++ row) {
      for (std::size_t col = 0; col < board_col_size; ++ col) {
        if (board[row][col] == 'X'
            && (col == 0 || board[row][col-1] != 'X')
            && (row == 0 || board[row - 1][col] != 'X')) {
          ++ reval;
        }
      }
    }

    return reval;
  }
};
