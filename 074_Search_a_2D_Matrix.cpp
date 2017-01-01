/*
Don't treat it as a 2D matrix, just treat it as a sorted list.
*/

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

/*
Binary search to find the right row at first.
Then binary search the target row.
*/
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

/*
In previous solution, the second binary search can be replaced with std::lower_bound.
 */

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
