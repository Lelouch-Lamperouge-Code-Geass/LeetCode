public class Solution {
    public void solveSudoku(char[][] board) {
        trySolve(board, 0, 0);
    }

    private boolean trySolve(char[][] board, int row, int col) {
        if (row == 9) return true;
        if (board[row][col] == '.') {
            for (char fill = '1'; fill <= '9'; ++fill) {
                if (isValid(board, row, col, fill)) {
                    board[row][col] = fill;

                    if ( (col == 8 && trySolve(board, row + 1, 0))
                         || (col  < 8 && trySolve(board, row, col + 1))
                         ) return true;

                    board[row][col] = '.';
                }
            }
            return false; // can't fill this cell
        } else {
            return (col == 8 && trySolve(board, row + 1, 0) )
                || (col  < 8 && trySolve(board, row, col + 1) );
        }
    }

    private boolean isValid(char[][] board, int row, int col, char fill) {

        // Check row
        for (int i = 8; i >= 0; --i) {
            if (board[i][col] == fill) return false;
        }

        // Check column
        for (int i = 8; i >= 0; --i) {
            if (board[row][i] == fill) return false;
        }

        // Check box
        int start_row = row / 3 * 3, start_col = col / 3 * 3;
        for (int i = start_row; i < start_row + 3; ++i) {
            for (int j = start_col; j < start_col + 3; ++j) {
                if (board[i][j] == fill) return false;
            }
        }

        return true;
    }
}
