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

a) Originally, the normal way to calculate the multiplication of two metrics A, and B is as follow:
We take the the all values from the first line of A, and all values from the first column of B, and multiply the corresponding values and sum them up, the final sum is the value for the location of first column and first row in final result matrix. Similarly, the value at [i][ j ] of result matrix C, which is C[ i ][ j ] is calculated as:

```C[ i ][ j ] = A[ i ][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j] + ... A[i][K]*B[K][j]```

( which is the sum of each multiplication of corresponding K values from row i of A and K values from column j of B )
```The Key is: if we calculate it this way, we finishing calculating the final value for the result matrix at once```

Then the brute force solution is as follow:

```java
public class Solution {
        public int[][] multiply(int[][] A, int[][] B) {
            int m = A.length, n = A[0].length, nB = B[0].length;
            int[][] C = new int[m][nB];

            for(int i = 0; i < m; i++) {
                    for (int j = 0; j < nB; j++) {
                        for(int k = 0; k < n; k++) {
                             C[i][j] += A[i][k] * B[k][j];
                        }
                    }
            }
            return C;  
        }
}
```

b) The smart solution, the key part of smart solution is that: it does not calculate the final result at once, and it takes each value from A, and calculate and partial sum and accumulate it into the final spot:
For example, for each value A[i][k], if it is not zero, it will be used at most nB times ( n is B[0].length ), which can be illustrated as follow:
Generally for the following equation:

```
C[ i ][ j ] = A[ i ][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j] + ... A[i][k]*B[k][j] .... A[i][K]*B[K][j]
j can be from 0 to nB, if we write all of them down, it will like following:
[For i from 0 to nB
C[ i ][ 0 ]=A[ i ][0]*B[0][0] + A[i][1]*B[1][0] + A[i][2]*B[2][0] + ... A[i][k]B[k][0] .... A[i][K]*B[K][0]
C[ i ][ 1 ]=A[ i ][0]*B[0][1] + A[i][1]*B[1][1] + A[i][2]*B[2][1] + ... A[i][k]B[k][0] .... A[i][K]*B[K][1]
...
C[ i ][ nB ]=A[ i ][0]*B[0][nB] + A[i][1]*B[1][nB] + A[i][2]*B[2][nB] + ... A[i][k]B[k][nB] .... A[i][K]*B[K][nB]
```

As you can see from above: for the same value A[i][k] from the first matrix, it will be used at most nB times if A[i][k] is not zero. And the smart solution is taking advantage of that!!!, the smart solution can be described as:

For each value A[i][k] in matrix A, if it is not zero, we calculate A[i][k] * B[k][j] and accumulate it into C[ i ][ j ] (Key part: the C[ i ][ j ] by now is not the final value in the result matrix !! Remember, in the brute force solution, the final value of C[i][j], takes sum of all multiplication values of K corresponding values from A and B? here C[ i ][ j ] is only sum of some multiplication values, NOT ALL until the program is done )

__BY NOW, it is very clear that, if the value A[ i ][ k ] from matrix is zero, we skip a For-loop- calculation, which is a loop iterating nB times, and this is the key part of why the smart solution is smart!!!__

The smart Solution Code is as follow:

```java
public class Solution {
    public int[][] multiply(int[][] A, int[][] B) {
        int m = A.length, n = A[0].length, nB = B[0].length;
        int[][] C = new int[m][nB];

        for(int i = 0; i < m; i++) {
            for(int k = 0; k < n; k++) {
                if (A[i][k] != 0) {
                    for (int j = 0; j < nB; j++) {
                        if (B[k][j] != 0) C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        return C;   
    }
}
```

c) "Sparse matrix manipultion" helps, if we compress the first sparse matrix into rows of lists( in each row list, it contains ( value, index ) pair ), we actually don't need to go over all values in a row in matrix A when are calculating the final result matrix. But Overall, it does not help improve run time algorithmatically!!

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

We can still optimize a little bit based on above solution.

```cpp
vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
  const std::size_t a_row_size = A.size(), a_col_size = A[0].size();
  const std::size_t b_row_size = B.size(), b_col_size = B[0].size();

  vector<vector<int>> res(a_row_size, vector<int>(b_col_size, 0));
  vector< vector<int> > sparse_a(a_row_size, vector<int>());

  for(int i = 0; i < a_row_size; i++) {
    for(int j = 0; j < a_col_size; j++) {
      if (A[i][j] != 0)  {
        sparse_a[i].emplace_back(j);
      }
    }
  }
  // C[i,j] = Sum(A[i,k] * B[k, j] for each k)
  for (int i = 0; i < a_row_size; ++i) {
    for (int k : sparse_a[i]) {
      for (int j = 0; j < b_row_size; ++j) {
        if (B[k][j] != 0) {
          res[i][j] += A[i][k] * B[k][j];
        }
      }
    }
  }
}
```
