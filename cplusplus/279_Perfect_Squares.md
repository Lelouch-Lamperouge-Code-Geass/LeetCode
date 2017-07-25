Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

# Solution
  
```cpp  
class Solution {
public:
    int numSquares(int n) {
        static std::vector<int> least_square_sum_count = {0, 1};
        int num = least_square_sum_count.size();
        while (num <= n) {
            int min_val = INT_MAX;
            for (int val = 1; val * val <= num; ++val) {
                min_val = std::min(min_val, 1 + least_square_sum_count[num - val * val]);
            }
            least_square_sum_count.push_back(min_val);
            ++ num;
        }
        
        return least_square_sum_count[n];
    }
};
```
