Given a picture consisting of black and white pixels, find the number of black lonely pixels.

The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

##### Example:

```
Input: 
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.
```

##### Note:

The range of width and height of the input 2D array is [1,500].

# Solution

__O(mn) Time, O(m+n) Space__

```cpp
class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        if (picture.empty()) return 0;
        const std::size_t row_size(picture.size()), col_size(picture[0].size());
        vector<int> row_counter(row_size, 0), col_counter(col_size, 0);
        for (std::size_t i = 0; i < row_size; ++i) {
            for (std::size_t j = 0; j < col_size; ++j) {
                if (picture[i][j] == 'B') {
                    ++ row_counter[i], ++ col_counter[j];
                }
            }
        }
        
        int reval(0);
        for (std::size_t i = 0; i < row_size; ++i) {
            for (std::size_t j = 0; j < col_size; ++j) {
                if (picture[i][j] == 'B'
                   && row_counter[i] == 1
                   && col_counter[j] == 1) {
                    ++ reval;
                }
            }
        }
        
        return reval;
    }
};
```

This solution can be optimized to __O(mn) Time, O(1) Space__.

