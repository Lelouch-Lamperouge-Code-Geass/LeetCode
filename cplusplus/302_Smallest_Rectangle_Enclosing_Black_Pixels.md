
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

```
[
  "0010",
  "0110",
  "0100"
]
```

and x = 0, y = 2,

 

Return 6.

# Solution

Of course, you can check all the cells in the matrix and mark a flag for very row and column if a cell has black pixel, which has time complexity O(mn).

However, we can do better than that because in the description, it gives out one location of black pixel.

Suppose we have a 2D array

```
"000000111000000"
"000000101000000"
"000000101100000"
"000001100100000"
```

Imagine we project the 2D array to the bottom axis with the rule "if a column has any black pixel it's projection is black otherwise white". The projected 1D array is

``` "000001111100000"  ```

```
Theorem : If there are only one black pixel region, 
  then in a projected 1D array all the black pixels are connected.

Proof by contradiction

Assume to the contrary that there are disconnected black pixels at i and j 
where i < j in the 1D projection array. 
Thus there exists one column k, k in (i, j) and and the column k in the 2D array has no black pixel. 
Therefore in the 2D array there exists at least 2 black pixel regions separated by column k 
which contradicting the condition of "only one black pixel region".
```  

Therefore we conclude that all the black pixels in the 1D projection array is connected.
  
This means we can do a binary search in each half to find the boundaries, if we know one black pixel's position. And we do know that.

To find the left boundary, do the binary search in the [0, y) range and find the first column vector who has any black pixel.

To determine if a column vector has a black pixel is O(m) so the search in total is O(m log n)

We can do the same for the other boundaries. The area is then calculated by the boundaries.
Thus the algorithm runs in __O(m log n + n log m)__.  
  
#  Solution

### Solution one

```cpp
int getLeftMostColumn(const std::vector< std::vector<char> > & image,
                int begin_row,
                int end_row,
                int begin_col,
                int end_col) {
  while (begin_col < end_col) {
    int mid_col = begin_col + (end_col - begin_col) / 2;

    // Check mid_col has '1' or not
    int row(begin_row);
    while (row <= end_row && '0' == image[row][mid_col]) ++ row;

    if (row == end_row + 1) { // The whole mid column has no '1'
      begin_col = mid_col + 1;
    } else { // The mid column has '1'
      end_col = mid_col;
    }
  }
  return begin_col;
}

int getRightMostColumn(const std::vector< std::vector<char> > & image,
                      int begin_row,
                      int end_row,
                      int begin_col,
                      int end_col) {
  while (begin_col < end_col) {
    int mid_col = begin_col + (end_col + 1 - begin_col) / 2; // Here mid_col is end_col inclination

    // Check mid_col has '1' or not
    int row(begin_row);
    while (row <= end_row && '0' == image[row][mid_col]) ++ row;

    if (row == end_row + 1) { // The whole mid column has no '1'
      end_col = mid_col - 1;
    } else { // The mid column has '1'
      begin_col = mid_col;
    }
  }

  return begin_col;
}

int getTopMostRow(const std::vector< std::vector<char> > & image,
                      int begin_row,
                      int end_row,
                      int begin_col,
                      int end_col) {
  while (begin_row < end_row) {
    int mid_row = begin_row + (end_row - begin_row) / 2;

    // Check mid_row has '1' or not
    int col(begin_col);
    while (col <= end_col && '0' == image[mid_row][col]) ++ col;

    if (col == end_col + 1) { // The whole mid row has no '1'
      begin_row = mid_row + 1;
    } else { // The mid row has '1'
      end_row = mid_row;
    }
  }

  return begin_row;
}


int getBottomMostRow(const std::vector< std::vector<char> > & image,
                       int begin_row,
                       int end_row,
                       int begin_col,
                       int end_col) {
  while (begin_row < end_row) {
    int mid_row = begin_row + (end_row + 1 - begin_row) / 2; // Here mid_row is end_row inclination

    // Check mid_row has '1' or not
    int col(begin_col);
    while (col <= end_col && '0' == image[mid_row][col]) ++ col;

    if (col == end_col + 1) { // The whole mid row has no '1'
      end_row = mid_row - 1;
    } else { // The mid row has '1'
      begin_row = mid_row;
    }
  }

  return begin_row;
}

int minArea(const std::vector< std::vector<char> > & image,
            int x,
            int y) {
  if (image.empty()) return 0;
  const int row_size(image.size()), col_size(image[0].size());
  int left_most_column = getLeftMostColumn(image, 0, row_size - 1, 0, y);
  int right_most_column = getRightMostColumn(image, 0, row_size - 1, y, col_size - 1);
  std::cout << left_most_column << ',' << right_most_column << std::endl;
  int top_most_row = getTopMostRow(image, 0, x, left_most_column, right_most_column);
  int bottom_most_row = getBottomMostRow(image, x, row_size - 1, left_most_column, right_most_column);
  std::cout << top_most_row << ',' << bottom_most_row << std::endl;
  return (right_most_column - left_most_column + 1) * (bottom_most_row - top_most_row + 1);
}

```
                                                        
### Solution two

We can combine some functions which have similar code into one function. However, I would say this is optional since the merged code is not a clear as solution one.

```cpp
#include <iostream>
#include <vector>

int SearchColumn(const std::vector< std::vector<char> > & image,
                 int begin_row,
                 int end_row,
                 int begin_column,
                 int end_column,
                 bool search_left_most) {
  while (begin_column < end_column) {
    int row(begin_row), mid_column = begin_column + (end_column - begin_column) / 2;
    while (row <= end_row && image[row][mid_column] == '0') ++ row;

    if (search_left_most) {
      if (row > end_row) {
        begin_column = mid_column + 1;
      } else {
        end_column = mid_column;
      }
      return begin_column;
    } else {
      if (row > end_row) {
        end_column = mid_column;
      } else {
        begin_column = mid_column + 1;
      }
      return end_column - 1;
    }
  }
}

int SearchRow(const std::vector< std::vector<char> > & image,
                 int begin_row,
                 int end_row,
                 int begin_column,
                 int end_column,
                 bool search_top_most) {
  while (begin_row < end_row) {
    int col(begin_column), mid_row = begin_row + (end_row - begin_row) / 2;
    while (col <= end_column && image[mid_row][col] == '0') ++ col;
    if (col > end_column && search_top_most) {
      begin_row = mid_row + 1;
    } else {
      end_row = mid_row;
    }
  }

  return begin_row;
}

// Thus the algorithm runs in O(m log n + n log m)
int minArea(const std::vector< std::vector<char> > & image,
            int x, int y) {
  if (image.empty()) return 0;
  const int row_size(image.size()), col_size(image[0].size());
  int left_most_column = SearchColumn(image, 0, row_size - 1, 0, y, true);
  int right_most_column = SearchColumn(image, 0, row_size - 1, y, col_size - 1, false);
  int top_most_row = SearchRow(image, 0, x, left_most_column, right_most_column, true);
  int bottom_most_row = SearchRow(image, x, row_size - 1, left_most_column, right_most_column, false);
  std::cout << left_most_column << ',' << right_most_column << std::endl;
  std::cout << top_most_row << ',' << bottom_most_row << std::endl;
  return (right_most_column - left_most_column + 1) * (bottom_most_row - top_most_row + 1);
}


int main() {
  std::vector< std::vector<char> > image = {
    {'0','0','1','0'},
    {'0','1','1','0'},
    {'0','1','0','0'}
  };
  std::cout << minArea(image, 2, 1) << std::endl;
  return 0;
}

```


