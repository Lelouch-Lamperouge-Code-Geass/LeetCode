Given an index k, return the kth row of the Pascal's triangle.  

For example, given k = 3,  
Return [1,3,3,1].  

__Note:__  
Could you optimize your algorithm to use only O(k) extra space?  

# Solution

The space complexity is required to be  only O(k) extra space. Therefore, we can't generate the whole triangle and return the rowIndex one.

We need find a way from one row to eveol to the next row.

```
1
11
121
1331
13641
```

We know that ```row[i][j] = row[i - 1][j - 1] + row[i - 1][j]```, and since we need to use only O(k) extra space, we can't use ```row[i-1]``` here. 

But that should not be hard, because we can use ```row[i][j] += row[i][j - 1]``` as long as we do it backwards on that level.

Note that we must iteratively update the array __from the end to the beginning__. 

```cpp
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex < 0) return vector<int>();
        
        vector<int> reval(rowIndex + 1, 0);
        reval[0] = 1;
        
        for (int i = 1; i <= rowIndex; ++i) {
            for (int j = i; j > 0; --j) {
                reval[j] += reval[j - 1];
            }
        }
        
        return reval;
    }
};

```
