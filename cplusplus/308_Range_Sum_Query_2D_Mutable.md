Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

![alt](https://leetcode.com/static/images/courses/range_sum_query_2d.png)

The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

```
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
```

Note:  
1. The matrix is only modifiable by the update function.  
2. You may assume the number of calls to update and sumRegion function is distributed evenly.  
3. You may assume that row1 ≤ row2 and col1 ≤ col2.  

# Solution

A simple solution is to run a loop  calculate sum of elements. To update a value, simply do matrix[i][j] = x. The first operation takes O(m*n) time and second operation takes O(1) time. Another simple solution is to create another matrix and store sum from start to matrix[i][j]. Sum of a given range can now be calculated in O(1) time, but update operation takes O(m*n) time now. This works well if the number of query operations are large and very few updates.

Since we are going to calculate the sum range with _mutable_ elements, we need to use segment tree or binary indexed tree.

Here we are going to use binary indexed tree. Binary Indexed Tree and Segment Tree both can do update/query in O(Logn) time. __The advantages of Binary Indexed Tree over Segment are, requires less space and very easy to implement.__

* http://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/

We know that to answer range sum queries on a 1-D array efficiently, binary indexed tree (or Fenwick Tree) is the best choice (even better than segment tree due to less memory requirements and a little faster than segment tree).

Can we answer sub-matrix sum queries efficiently using Binary Indexed Tree ? The answer is yes. This is possible using a 2D BIT which is nothing but an array of 1D BIT(Note: I think this statement might be wrong, I would say it is a BIT of BIT.).

2D BIT is basically a BIT where each element is another BIT.
Updating by adding v on (x, y) means it's effect will be found throughout the rectangle [(x, y), (max_x, max_y)], and query for (x, y) gives you the result of the rectangle [(0, 0), (x, y)], assuming the total rectangle is [(0, 0), (max_x, max_y)]. So when you query and update on this BIT,you have to be careful about how many times you are subtracting a rectangle and adding it. Simple set union formula
works here. 
 
So if you want to get the result of a specific rectangle
[(x1, y1), (x2, y2)], the following steps are necessary:

``` 
Query(x1,y1,x2,y2) = getSum(x2, y2)-getSum(x2, y1-1) -
                     getSum(x1-1, y2)+getSum(x1-1, y1-1)
```

Here 'Query(x1,y1,x2,y2)' means the sum of elements enclosed in the rectangle with bottom-left corner's co-ordinates (x1, y1) and top-right corner's co-ordinates - (x2, y2)
 
```Constraints -> x1<=x2 and y1<=y2```

```
    /\
 y  |
    |           --------(x2,y2)
    |          |       |
    |          |       |
    |          |       |
    |          ---------
    |       (x1,y1)
    |
    |___________________________
   (0, 0)                   x-->
```   


```cpp
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return;
        nrow = matrix.size();
        ncol = matrix[0].size();
        nums = matrix;
        BIT = vector<vector<int>> (nrow+1, vector<int>(ncol+1, 0));
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                add(i, j, matrix[i][j]);
            
    }

    void update(int row, int col, int val) {
        int diff = val - nums[row][col];
        add(row, col,diff);
        nums[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int regionL = 0, regionS = 0;
        int regionLeft = 0, regionTop = 0;

        regionL = region(row2, col2);
        
        if (row1 > 0 && col1 > 0) regionS = region(row1-1, col1-1);
        
        if (row1 > 0) regionTop  = region(row1-1, col2);
            
        if (col1 > 0) regionLeft = region(row2, col1-1);       
 
        return regionL - regionTop - regionLeft + regionS;
    }
private:
    vector<vector<int>> nums;
    vector<vector<int>> BIT;
    int nrow = 0;
    int ncol = 0;
    void add(int row, int col, int val) {
        row++;
        col++;
        while(row <= nrow) {
            int colIdx = col;
            while(colIdx <= ncol) {
                BIT[row][colIdx] += val;
                colIdx += (colIdx & (-colIdx));
            }
            row +=  (row & (-row));
        }
    }
    
    int region(int row, int col) {
        row++;
        col++;
        int res = 0;
        while(row > 0) {
            int colIdx = col;
            while(colIdx > 0) {
                res += BIT[row][colIdx];
                colIdx -= (colIdx & (-colIdx));
            }
            row -= (row & (-row));
        }
        return res;
    }
};
```

