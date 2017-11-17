Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:

```
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
```

# Solution

Note that start_row <= end_row && start_col <= end_col is the requirement to enter the while loop, which is in fact the INVARIANT we need. And every "strip" (increase start_row or start_col / decrease end_row or end_col) also has its own requirement too. Therefore, whenever we need to update start_row, start_col, end_row, end_col, we need to check whether we violate the invariant or not.

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> reval(n,vector<int>(n,0));
        int min_row(0), max_row(n-1), min_col(0), max_col(n-1),val(1);
        while(min_row<=max_row && min_col<=max_col){
            //top row
            for(int i=min_col;i<=max_col;++i){
                reval[min_row][i] = val;
                ++ val;
            }
            ++ min_row; //strip off top row
            
            //rightmost column
            for(int i=min_row;i<=max_row;++i){
                reval[i][max_col] = val;
                ++ val;
            }
            -- max_col; //strip off rightmost column
            
            if(min_col<=max_col){
                //bottom row
                for(int i=max_col;i>=min_col;--i){
                    reval[max_row][i] = val;
                    ++ val;
                }
                -- max_row; // strip off bottom column
            }
            
            if(min_row<=max_row){
                //rightmost column
                for(int i=max_row;i>=min_row;--i){
                    reval[i][min_col] = val;
                    ++ val;
                }
                ++ min_col; // strip off leftmost column
            }
        }
        
        return reval;
    }
};
```
