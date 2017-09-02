Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

* Integers in each row are sorted from left to right.
* The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

```
[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
```

Given target = 3, return true.
  
# Solution
  
### Solution 1  

Don't treat it as a 2D matrix, just treat it as a sorted list.
  
Use binary search.

n * m matrix convert to an array => matrix[x][y] => a[x * m + y]

an array convert to n * m matrix => a[x] =>matrix[x / m][x % m];  

```cpp
class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int l = 0, r = m * n - 1;
    while (l != r){
      int mid = (l + r - 1) >> 1;
      if (matrix[mid / m][mid % m] < target)
        l = mid + 1;
      else
        r = mid;
    }
    return matrix[r / m][r % m] == target;
  }
};
```

Or

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        
        const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
        
        std::size_t low(0), high(row_size * col_size - 1);
        
        while (low <= high) {
            std::size_t mid = low + (high - low) / 2;
            std::size_t i = mid / col_size, j = mid % col_size;
            if (matrix[i][j] > target) {
                if (0 == mid) break; 
                high = mid - 1;
            } else if (matrix[i][j] < target) {
                low = mid + 1;
            } else {
                return true;
            }
        }
        
        return false;
    }
};
```

### Solution 2
Binary search to find the right row at first.
Then binary search the target row.
  
```cpp
class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int low(0), high(matrix.size()-1);
    while (low<=high) {
      int mid = low + (high - low) / 2;
      if (matrix[mid][0] == target) {
        return true;
      } else if(matrix[mid][0] > target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    // Here high is pointing to the right row
    if (high==-1) return false;
    const std::vector<int> & target_row = matrix[high];
    low = 0, high = target_row.size()-1;
    while (low<=high) {
      int mid = low + (high - low) / 2;
      if (target_row[mid] == target) {
        return true;
      } else if (target_row[mid]<target) {
        low = mid + 1;
      } else {
        high = mid -1;
      }
    }
    return false;
  }
};
```

In previous solution, the second binary search can be replaced with std::lower_bound.
 
```cpp
class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int low(0), high(matrix.size()-1);
    while (low<=high) {
      int mid = low + (high - low) / 2;
      if (matrix[mid][0] == target) {
        return true;
      } else if(matrix[mid][0] > target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    // Here high is pointing to the right row
    if (high==-1) return false;
    const std::vector<int> & target_row = matrix[high];
    auto iter = std::lower_bound(target_row.begin(),target_row.end(),target);
    return iter!=target_row.end() && *iter == target;

  }
};
```
