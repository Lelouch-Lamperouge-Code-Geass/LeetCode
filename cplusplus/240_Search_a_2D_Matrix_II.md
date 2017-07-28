Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

1. Integers in each row are sorted in ascending from left to right.  
2. Integers in each column are sorted in ascending from top to bottom.  
  
For example,

Consider the following matrix:

```
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
```

Given target = 5, return true.

Given target = 20, return false.
  
# Solution

The most straightforward solution is to run binary search on each row, and its time complexity is O(row_size * log(col_size)).
This will work but if you think about this solution, you will find that it only uses property 1, "Integers in each row are sorted". How about property 2? 

Then you may say, let's do binary search on first column and then do binary search on row. But this is a wrong solution, because the first number of each row isn't necessarily larger than all the numbers with smaller row. 
  
This means we need to think outside the box.
  
If you look at the matrix carefully, you will find that if we place a chess piece at the top-right corner or bottom-left corner, we can move the chess piece in a decisive direction based on its value comparing to target. Actually the matrix looks like the it contains two "binary search tree" and it has two "roots" correspondingly.
  
Let's say we place the chess piece on top-right corner, and begin to move it. And all numbers on its "left" are smaller than it, all numbers on its "right(bottom direction)" are larger than it. Therefore we can essentially do a binary search on a binary tree. It also works if we begin with bottom-left corner. It won't work if we place the chess piece on top-left and bottom-right, because it won't form a binary search tree.
  
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
        std::size_t row_pos(0), col_pos(col_size - 1);
        while (row_pos < row_size && col_pos >= 0) {
            if (target > matrix[row_pos][col_pos]) {
                ++ row_pos;
            } else if (target < matrix[row_pos][col_pos]) {
               if (col_pos > 0) {
                   -- col_pos ;
               } else {
                   break;
               }
            } else { // target == matrix[row_pos][col_pos]
                return true;
            }
        }
        
        return false;
    }
};
```
