Given numRows, generate the first numRows of Pascal's triangle.  

For example, given numRows = 5,  
Return  

```
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

# Solution

The key is to realize that ```reval[i][j] = reval[i - 1][j - 1] + reval[i - 1][j]```.

```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows <= 0) return vector<vector<int>>();
        
        vector<vector<int>> reval(1, vector<int>(1, 1));
        
        for (int i = 1; i < numRows; ++i) {
            reval.emplace_back(i + 1, 0);
            int begin(0), end(i);
            reval[i][begin] = reval[i][end] = 1;
            for (int j = begin + 1; j < end; ++j) {
                reval[i][j] = reval[i - 1][j - 1] + reval[i - 1][j];
            }
        }
        
        return reval;
    }
};
```
