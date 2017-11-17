The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
  
![alt](https://leetcode.com/static/images/problemset/8-queens.png)

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:   
       
```
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
```

# Solution

Similar to ["solve sudoku" problem](https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/037_Sudoku_Solver.md).

First of all, we need a function IsValid to check whether a partially filled chessboard is valid.

Once we have such a function, the rest is simple. We begin to fill empty square, and check whether the chessboard is still valid after we fill it with a queen. If it is, keep going forward for next empty square; if it is not, recall this fill.

As you can see, after we fill an empty square, we get a partial candidate. The partial candidate represents a tree node in a potential search tree. We check every partial candidate whether it can be extended further. If it can't, the whole sub-tree rooted at that square is skipped (__pruned__).
       
```cpp
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
```

# Knowledge

### Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each __partial candidate__ ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

_Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution._ It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.
                                                                                         
The backtracking algorithm enumerates a set of __partial candidates__ that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps.
Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
                                                                                         
The backtracking algorithm traverses this search tree recursively, from the root down, in _depth-first order_. At each node c, the algorithm checks whether c can be completed to a valid solution. _If it cannot, the whole sub-tree rooted at c is __skipped (pruned)__._ Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.
                                                                                         
Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. __The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node.__ This fact should be considered when choosing the potential search tree and implementing the pruning test.                                                                                         
       
