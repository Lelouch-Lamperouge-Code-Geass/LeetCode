public class Solution {
    public boolean isValidSudoku(char[][] board) {
        boolean[][] row_marker = new boolean[9][9];
        boolean[][] col_marker = new boolean[9][9];
        boolean[][] box_marker = new boolean[9][9];

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    int val = board[i][j] - '0' - 1;
                    if (row_marker[i][val] || col_marker[j][val] || box_marker[i/3 * 3 + j / 3][val])
                        return false;
                    row_marker[i][val] = col_marker[j][val] = box_marker[i/3 * 3 + j / 3][val] = true;
                }
            }
        }

        return true;
    }
}
