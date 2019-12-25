Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
```
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
```

# Solution

This is a very simple and easy to understand solution. I traverse right and increment rowBegin, then traverse down and decrement colEnd, then I traverse left and decrement rowEnd, and finally I traverse up and increment colBegin.

The only tricky part is that when I traverse left or up I have to check whether the row or col still exists to prevent duplicates. 

__Note that start_row<=end_row && start_col<=end_col is the requirement to enter the while loop, which is in fact the INVARIANT we need. Therefore, whenever we need to update start_row, start_col, end_row, end_col, we need to check whether we violate the invariant or not.__

### Code

```java
class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> reval = new ArrayList<>();

        if (matrix == null || matrix.length == 0) return reval;

        int startRow = 0, startCol = 0;
        int endRow = matrix.length - 1, endCol = matrix[0].length - 1;

        while (startRow <= endRow || startCol <= endCol) {

            // Peel off topmost row
            if (startRow <= endRow) {
                for (int i = startCol; i <= endCol; ++i) {
                    reval.add(matrix[startRow][i]);
                }
                ++ startRow;
            }

            // Peel off rightmost column
            if (startCol <= endCol) {
                for (int i = startRow; i <= endRow; ++i) {
                    reval.add(matrix[i][endCol]);
                }
                -- endCol;
            }

            // Peel off bottommost row
            if (startRow <= endRow) {
                for (int i = endCol; i >= startCol; --i) {
                    reval.add(matrix[endRow][i]);
                }
                -- endRow;
            }

            // Peel off leftmost column
            if (startCol <= endCol) {
                for (int i = endRow; i >= startRow; --i) {
                    reval.add(matrix[i][startCol]);
                }
                ++ startCol;
            }
        }

        return reval;
    }
}
```
