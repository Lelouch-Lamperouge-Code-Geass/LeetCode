Determine if a Sudoku is valid, according to: [Sudoku Puzzles - The Rules](http://sudoku.com.au/TheRules.aspx).

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)

A partially filled sudoku which is valid.

##### Note:

A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

# Solution

This problem is simple.

You just need a "marker" for every row, column and box. If a number(0-9) is present, mark the corresponding entry in the "marker".

Below solution uses a 9x9 matrix as the "marker".

If the interviewer ask you to improve the space complexity, note that theoretically you just need 9*9 entries in each marker and the entry can be a bit.

Therefore, you can optimize the space complexity to 9*9*3 bits.

The time complexity will always be O(N^2).

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row_marker[9][9] = {false},
        col_marker[9][9]={false},
        box_marker[9][9]={false};
        for(std::size_t row=0;row<9;++row){
            for(std::size_t col=0;col<9;++col){
                if(board[row][col] != '.'){
                    int num(board[row][col]-'0'), box_num(row /3 * 3 + col /3);
                    if(row_marker[row][num-1] || col_marker[col][num-1] || box_marker[box_num][num-1]){
                        return false;
                    } else {
                        row_marker[row][num-1] = col_marker[col][num-1] = box_marker[box_num][num-1] = true;
                    }
                }
            }
        }
        return true;
    }
};
```
