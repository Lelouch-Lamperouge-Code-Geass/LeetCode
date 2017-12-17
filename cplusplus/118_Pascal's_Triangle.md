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

# Knowledge

### Pascal's triangle

In mathematics, Pascal's triangle is a triangular array of the binomial coefficients. In much of the Western world, it is named after French mathematician Blaise Pascal, although other mathematicians studied it centuries before him in India, Persia (Iran), China, Germany, and Italy.

The rows of Pascal's triangle are conventionally enumerated starting with row n = 0 at the top (the 0th row). The entries in each row are numbered from the left beginning with k = 0 and are usually staggered relative to the numbers in the adjacent rows. The triangle may be constructed in the following manner: In row 0 (the topmost row), there is a unique nonzero entry 1. Each entry of each subsequent row is constructed by adding the number above and to the left with the number above and to the right, treating blank entries as 0. For example, the initial number in the first (or any other) row is 1 (the sum of 0 and 1), whereas the numbers 1 and 3 in the third row are added to produce the number 4 in the fourth row.

![alt](https://upload.wikimedia.org/wikipedia/commons/c/ca/Pascal_triangle_small.png)

##### Binomial expansions

Pascal's triangle determines the coefficients which arise in binomial expansions. For an example, consider the expansion:

![alt](http://www.mathnstuff.com/math/algebra/tt/tt43h.gif)

Notice the coefficients are the numbers in row two of Pascal's triangle: 1, 2, 1. In general, when a binomial like x + y is raised to a positive integer power we have:

![alt](https://cdn-images-1.medium.com/max/1600/1*PHraeWdzWdmOfl2JhRdTVg.png)
