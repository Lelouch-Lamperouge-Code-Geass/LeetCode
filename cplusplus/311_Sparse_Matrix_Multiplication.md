Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

```
A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
```

# Solution

In numerical analysis and computer science, __a sparse matrix or sparse array is a matrix in which most of the elements are zero__. By contrast, if most of the elements are nonzero, then the matrix is considered dense. The number of zero-valued elements divided by the total number of elements (e.g., m × n for an m × n matrix) is called the sparsity of the matrix (which is equal to 1 minus the density of the matrix).


In the case of a sparse matrix, substantial memory requirement reductions can be realized by storing only the non-zero entries. Depending on the number and distribution of the non-zero entries, different data structures can be used and yield huge savings in memory when compared to the basic approach. The trade-off is that accessing the individual elements becomes more complex and additional structures are needed to be able to recover the original matrix unambiguously.

The matrix
```
A =	
[2.0	-1.0	0	0
-1.0	2.0	-1.0	0
0	-1.0	2.0	-1.0
0	0	-1.0	2.0]
```
is represented in this way as
```
A = [[(0, 2.0), (1, -1.0)],
     [(0, -1.0), (1, 2.0), (2, -1.0)],
     [(1, -1.0), (2, 2.0), (3, -1.0)],
     [(2, -1.0), (3, 2.0)]]
```     
where A is a nested sequence. 

```cpp
 vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    const int rowA = A.size(), rowB = B.size();
    const int colA = A[0].size(), colB = B[0].size();
    vector<vector<int>> res(rowA, vector<int>(colB, 0));
    vector<vector<pair<int, int>>> sparseA(rowA, vector<pair<int,int>>());

    for(int i = 0; i < rowA; i++) {
       for(int j = 0; j < colA; j++) {
        if(A[i][j] != 0)  sparseA[i].emplace_back(j, A[i][j]);
       }
    }
     
    for (int i = 0; i < rowA; ++i) {
     for (auto noZeros : sparseA[i]) {
        for (int j = 0; j < rowB; ++j) {
            if(B[noZeros.first][j] != 0) res[i][j] += noZeros.second * B[noZeros.first][j];
        }
      }
    }
    return res;
}
```
