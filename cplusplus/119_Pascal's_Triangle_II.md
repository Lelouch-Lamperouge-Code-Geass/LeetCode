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

