/**
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2,

 

Return 6.
*/

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
