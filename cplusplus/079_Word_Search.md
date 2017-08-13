Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =
  
```
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
```

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
  
# Solution
  
```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || word.empty()) return false;       
        const std::size_t row_size(board.size()), col_size(board[0].size());
        for (std::size_t row = 0; row < row_size; ++ row) {
            for (std::size_t col = 0; col < col_size; ++ col) {
                if (board[row][col] == word[0] && findWithDfs(board, word, row, col, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
private:
    bool findWithDfs(vector<vector<char>>& board, 
                     const string &word,
                     const std::size_t row,
                     const std::size_t col,
                     const std::size_t pos) {
        const std::size_t row_size(board.size()), col_size(board[0].size());
        if (row >= row_size || col >= col_size) return false;
        if (board[row][col] == word[pos]) {
            if (pos == word.size() - 1) {
                return true;
            } else {
                const char c = board[row][col];
                board[row][col] = '#';
                bool found = findWithDfs(board, word, row - 1, col, pos + 1)
                    || findWithDfs(board, word, row + 1, col, pos + 1)
                    || findWithDfs(board, word, row, col - 1, pos + 1)
                    || findWithDfs(board, word, row, col + 1, pos + 1);
                board[row][col] = c ; // revert back
                return found;
            }
        } 
        
        return false;
    }
};
```
