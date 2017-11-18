You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

__Note__ : Given n will be a positive integer.
  
##### Example 1:

```
Input: 2
Output:  2
Explanation:  There are two ways to climb to the top.

1. 1 step + 1 step
2. 2 steps
```

##### Example 2:

```
Input: 3
Output:  3
Explanation:  There are three ways to climb to the top.

1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```


# Solution

This problem is very very similar to fibonacci problem.
  
Like most dynamic programming, it shows the "matrix/grid structure".
  
In general, dynamic programming show a "matrix/grid pattern". Why is that?

We know that dynamic programming is a method for solving a complex problem by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions. The next time the same subproblem occurs, instead of recomputing its solution, one simply looks up the previously computed solution, thereby saving computation time at the expense of a (hopefully) modest expenditure in storage space.

If such a problem's solution is based on one smaller subproblem, then the matrix is a 1 * n matrix, e.g. fibonacci sequence.

If such a problem's solution is based on multiple smaller subproblems, then the matrix is a m * n matrix, e.g. edit distance problem.  

```cpp
class Solution {
public:
  int climbStairs(int n) {
    if (n<=2) return n;
    vector<int> ways_count(n+1,0);
    ways_count[1] = 1, ways_count[2] = 2;
    for (int i=3;i<=n;++i) {
      ways_count[i] = ways_count[i-2] + ways_count[i-1];
    }
    return ways_count[n];
  }
};
```

We can optimize previous solution so that the space complexity is only O(1);

```cpp
class Solution {
public:
  int climbStairs(int n) {
    if (n<=2) return n;
    int two_steps_before = 1, one_step_before = 2;
    for (int i=3;i<=n;++i) {
      int cur = two_steps_before + one_step_before;
      two_steps_before = one_step_before;
      one_step_before = cur;
    }
    return one_step_before;
  }
};
```
