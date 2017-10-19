Given an Android 3x3 key lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the total number of unlock patterns of the Android lock screen, which consist of minimum of m keys and maximum n keys.

Rules for a valid pattern:

1. Each pattern must connect at least m keys and at most n keys.  
2. All the keys must be distinct.  
3. If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern. No jumps through non selected key is allowed.  
4. The order of keys used matters.  

![alt](https://leetcode.com/static/images/problemset/android-unlock.png)

Explanation:

```
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
```

```
Invalid move: 4 - 1 - 3 - 6 
Line 1 - 3 passes through key 2 which had not been selected in the pattern.

Invalid move: 4 - 1 - 9 - 2
Line 1 - 9 passes through key 5 which had not been selected in the pattern.

Valid move: 2 - 4 - 1 - 3 - 6
Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern

Valid move: 6 - 5 - 4 - 1 - 9 - 2
Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.
```

Example:

```
Given m = 1, n = 1, return 9.
```

# Solution

```cpp
class Solution {
public:
    Solution() : m_jumps(10, std::vector<int>(10, 0)) {
        // Row
        m_jumps[1][3] = m_jumps[3][1] = 2;
        m_jumps[4][6] = m_jumps[6][4] = 5;
        m_jumps[7][9] = m_jumps[9][7] = 8;
        
        // Col
        m_jumps[1][7] = m_jumps[7][1] = 4;
        m_jumps[2][8] = m_jumps[8][2] = 5;
        m_jumps[3][9] = m_jumps[9][3] = 6;
        
        // Dia
        m_jumps[1][9] = m_jumps[9][1] = 5;
        m_jumps[3][7] = m_jumps[7][3] = 5;
    }
    int numberOfPatterns(int m, int n){
        int count(0);
        vector<bool> visited(10, false);
        for (int i = m; i <= n; ++i) {
            count += 4 * dfs(1, visited, i - 1); // 1, 3, 7, 9 are symmetric
            count += 4 * dfs(2, visited, i - 1); // 2, 4, 6, 8 are symmetric
            count += dfs(5, visited, i - 1); // 5
        }
        return count;
    }
private:
    int dfs(int cur_num,
           vector<bool> &visited,
           int remain) {
        if (remain == 0) return 1;
        visited[cur_num] = true;
        int reval(0);
        for (int next = 1; next <= 9; ++next) {
            // If vis[i] is not visited 
            // and (two numbers are adjacent or skip number is already visited)
            if ( !visited[next] 
                && (m_jumps[cur_num][next] == 0
               || visited[m_jumps[cur_num][next]]) ){
                reval += dfs(next, visited, remain - 1);
            }
        }
        visited[cur_num] = false;
        return reval;
    }

    std::vector<std::vector<int>> m_jumps;
};
```
