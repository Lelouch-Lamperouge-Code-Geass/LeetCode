// The key observation is that in order to win Tic-Tac-Toe you must have the entire row or column.
// Thus, we don't need to keep track of an entire n^2 board. We only need to keep a count for each
// row and column. If at any time a row or column matches the size of the board then that player has won.
// To keep track of which player, I add one for Player1 and -1 for Player2. There are two
// additional variables to keep track of the count of the diagonals.
// Each time a player places a piece we just need to check the count of
// that row, column, diagonal and anti-diagonal.

class TicTacToe {
public:
  /** Initialize your data structure here. */
  TicTacToe(int n): rows(n), cols(n), N(n), diag(0), rev_diag(0) {}

  int move(int row, int col, int player) {
    int add = player == 1 ? 1 : -1;
    rows[row] += add;
    cols[col] += add;
    diag += (row == col ? add : 0);
    rev_diag += (row == N - col - 1 ? add : 0);
    return (abs(rows[row]) == N || abs(cols[col]) == N || abs(diag) == N || abs(rev_diag) == N) ? player : 0;
  }

private:
  vector<int> rows, cols;
  int diag, rev_diag, N;
};
