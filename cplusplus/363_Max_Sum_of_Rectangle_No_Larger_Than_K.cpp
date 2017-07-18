// https://www.youtube.com/watch?v=yCQN096CwWM
// https://www.quora.com/Given-an-array-of-integers-A-and-an-integer-k-find-a-subarray-that-contains-the-largest-sum-subject-to-a-constraint-that-the-sum-is-less-than-k

// For the solution below, I assume that the number of rows is larger than the number of columns.
// Thus in general time complexity is O[min(m,n)^2 * max(m,n) * log(max(m,n))], space O(max(m, n)).

class Solution {
public:
  int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int res(INT_MIN);// res can't be set as 0
    if (matrix.empty()) return res;
    const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
    for (std::size_t left = 0; left < col_size; ++ left) {
      // row_accu_sum record the accumulative sum of that row
      std::vector<int> row_accu_sum(row_size, 0);
      for (std::size_t right = left; right < col_size; ++ right) {

        for (std::size_t i = 0; i < row_size; ++ i) {
          row_accu_sum[i] += matrix[i][right];
        }

        std::set<int> accu_set;
        accu_set.insert(0); // important
        int cur_max(INT_MIN), rec_accu_sum(0);
        for (int sum : row_accu_sum) {
          rec_accu_sum += sum;
          set<int>::iterator iter = accu_set.lower_bound(rec_accu_sum - k);
          if (iter != accu_set.end()) {
            cur_max = std::max(cur_max, rec_accu_sum - (*iter) );
          }
          accu_set.insert(rec_accu_sum);
        }

        res = std::max(res, cur_max);
      }
    }

    return res;
  }
};
