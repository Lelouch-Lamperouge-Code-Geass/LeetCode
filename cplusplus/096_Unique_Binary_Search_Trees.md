Given n, how many structurally unique BST's (binary search trees) that store values 1...n?  

For example,  
Given n = 3, there are a total of 5 unique BST's.  

```
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

# Solution

If we pick a number from 1-n as a root number, then we can generate ```number_of_left_trees * number_of_right_trees``` trees. 

Then we get a solution like this :

```cpp
class Solution {
public:
    int numTrees(int n) {
        if (n <= 0) return 1; // Let's return 1 instead of 0 here
        if (n == 1) return 1;
        
        int reval(0);
        for (int i = 1; i <= n ; ++i) { // Choose i as root
            int left_count = numTrees(i - 1);
            int right_count = numTrees(n - i);
            reval += left_count * right_count;
        }
        
        return reval;
    }
};
```

__However, there are many re-calculations in this solution.__


Dynamic programming can be used to :  

1. Optimal solutions to some problems : The reason that dynamic programming can be used to find an optimal solutions is since we already "memorized" the solutions of all our sub-problems. We can just find current optimal solution based on those.   

2. Counting the number of solutions : The reason that dynamic programming can be used to counting the number of solutions is because we already "memorized" the count information of all sub-problems.



The problem can be solved in a dynamic programming way. I’ll explain the intuition and formulas in the following.

Given a sequence 1…n, to construct a Binary Search Tree (BST) out of the sequence, we could enumerate each number i in the sequence, and use the number as the root, naturally, the subsequence 1…(i-1) on its left side would lay on the left branch of the root, and similarly the right subsequence (i+1)…n lay on the right branch of the root. We then can construct the subtree from the subsequence recursively. Through the above approach, we could ensure that the BST that we construct are all unique, since they have unique roots.

The problem is to calculate the number of unique BST. To do so, we need to define two functions:

```G(n)```: the number of unique BST for a sequence of length n.

```F(i, n), 1 <= i <= n```: the number of unique BST, where the number i is the root of BST, and the sequence ranges from 1 to n.

As one can see, G(n) is the actual function we need to calculate in order to solve the problem. And G(n) can be derived from F(i, n), which at the end, would recursively refer to G(n).

First of all, given the above definitions, we can see that the total number of unique BST G(n), is the sum of BST F(i) using each number i as a root.
i.e.  

```
G(n) = F(1, n) + F(2, n) + ... + F(n, n). 
```

Particularly, the bottom cases, there is only one combination to construct a BST out of a sequence of length 1 (only a root) or 0 (empty tree).
i.e.

```
G(0)=1, G(1)=1. 
```

Given a sequence 1…n, we pick a number i out of the sequence as the root, then the number of unique BST with the specified root F(i), is the cartesian product of the number of BST for its left and right subtrees. For example, F(3, 7): the number of unique BST tree with number 3 as its root. To construct an unique BST out of the entire sequence [1, 2, 3, 4, 5, 6, 7] with 3 as the root, which is to say, we need to construct an unique BST out of its left subsequence [1, 2] and another BST out of the right subsequence [4, 5, 6, 7], and then combine them together (i.e. cartesian product). The tricky part is that we could consider the number of unique BST out of sequence [1,2] as G(2), and the number of of unique BST out of sequence [4, 5, 6, 7] as G(4). Therefore, F(3,7) = G(2) * G(4).

i.e.

```
F(i, n) = G(i-1) * G(n-i)	1 <= i <= n 
```

Combining the above two formulas, we obtain the recursive formula for G(n). i.e.

```
G(n) = G(0) * G(n-1) + G(1) * G(n-2) + … + G(n-1) * G(0) 
```

In terms of calculation, we need to start with the lower number, since the value of G(n) depends on the values of G(0) … G(n-1).

```cpp
class Solution {
public:
    int numTrees(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        
        vector<int> num_of_trees(n + 1, 0);
        num_of_trees[0] = num_of_trees[1] = 1;
        
        for (int i = 2; i <= n ; ++i) { 
            for (int left_num = 0; left_num < i; ++left_num) {
                num_of_trees[i] += num_of_trees[left_num] * num_of_trees[i - left_num - 1];
            }
        }
        
        return num_of_trees[n];
    }
};
```



# Knowledge

### Dynamic programming

__Dynamic programming__ (also known as dynamic optimization) is a method for solving a complex problem by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions. The next time the same subproblem occurs, instead of recomputing its solution, one simply looks up the previously computed solution, thereby saving computation time at the expense of a (hopefully) modest expenditure in storage space. (Each of the subproblem solutions is indexed in some way, typically based on the values of its input parameters, so as to facilitate its lookup.) The technique of storing solutions to subproblems instead of recomputing them is called _"memoization"_.

_Dynamic programming algorithms are often used for optimization. A dynamic programming algorithm will examine the previously solved subproblems and will combine their solutions to give the best solution for the given problem._ In comparison, a greedy algorithm treats the solution as some sequence of steps and picks the locally optimal choice at each step. Using a greedy algorithm does not guarantee an optimal solution, because picking locally optimal choices may result in a bad global solution, but it is often faster to calculate. Some greedy algorithms (such as Kruskal's or Prim's for minimum spanning trees) are however proven to lead to the optimal solution.

In addition to finding optimal solutions to some problems, dynamic programming can also be used for counting the number of solutions, for example counting the number of ways a certain amount of change can be made from a given collection of coins, or counting the number of optimal solutions to the coin change problem described above.

```
Dynamic programming can be used to :

1. optimal solutions to some problems  
2. counting the number of solutions

```
