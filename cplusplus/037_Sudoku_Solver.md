Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

A sudoku puzzle...
 
![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)
       
...and its solution numbers marked in red.
       
![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Sudoku-by-L2G-20050714_solution.svg/250px-Sudoku-by-L2G-20050714_solution.svg.png)       
 
# Solution
 
First of all, we need a function IsValid to check whether a partially filled sudoku is valid.
       
Once we have such a function, the rest is simple. We begin to fill empty box, and check whether the sudoku is still valid after we fill it with a number ('0'-'9'). If it is, keep going forward for next empty box; if it is not, recall this fill.
  
As you can see, after we fill an empty box, we get a partial candidate. The partial candidate represents a tree node in a _potential search tree_. We check every partial candidate whether it can be extended further. If it can't, the whole sub-tree rooted at c is skipped (_pruned_).
       
This is a classic backtracking problem, another classic problem is [eight queens puzzle](https://en.wikipedia.org/wiki/Eight_queens_puzzle).   
       

### Solution 1
// https://
// discuss.leetcode.com/topic/7195/sharing-my-2ms-c-solution-with-comments-and-explanations


### Solution 2 

```cpp       
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
```

### Solution 3

```cpp
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
```

# Knowledge

### Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each __partial candidate__ ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

_Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution._ It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.
                                                                                         
The backtracking algorithm enumerates a set of __partial candidates__ that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps.
Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
                                                                                         
The backtracking algorithm traverses this search tree recursively, from the root down, in _depth-first order_. At each node c, the algorithm checks whether c can be completed to a valid solution. _If it cannot, the whole sub-tree rooted at c is __skipped (pruned)__._ Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.
                                                                                         
Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. __The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node.__ This fact should be considered when choosing the potential search tree and implementing the pruning test.                                                                                         
       
