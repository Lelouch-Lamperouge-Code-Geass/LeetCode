A greedy algorithm is any algorithm that follows the problem-solving heuristic of making the locally optimal choice at each stage. In many problems, a greedy strategy __does not usually produce an optimal solution__, but nonetheless, a greedy heuristic may yield locally optimal solutions that __approximate a globally optimal solution in a reasonable amount of time__.

Greedy heuristics are known to produce suboptimal results on many problems, and so natural questions are:

* For which problems do greedy algorithms perform optimally?
* For which problems do greedy algorithms guarantee an approximately optimal solution?
* For which problems is the greedy algorithm guaranteed not to produce an optimal solution?

A large body of literature exists answering these questions for general classes of problems, such as __matroids__, as well as for specific problems, such as __set cover__.

A __matroid__ is a mathematical structure that generalizes the notion of linear independence from vector spaces to arbitrary sets. If an optimization problem has the structure of a matroid, then the appropriate greedy algorithm will solve it optimally.

Greedy algorithms typically (but not always) fail to find the globally optimal solution because they usually do not operate exhaustively on all the data. They can make commitments to certain choices too early which prevent them from finding the best overall solution later. For example, all known greedy coloring algorithms for the graph coloring problem and all other NP-complete problems do not consistently find optimum solutions. Nevertheless, they are useful because they are quick to think up and often give good approximations to the optimum.

If a greedy algorithm can be proven to yield the global optimum for a given problem class, it typically becomes the method of choice because it is faster than other optimization methods like dynamic programming. Examples of such greedy algorithms are Kruskal's algorithm and Prim's algorithm for finding minimum spanning trees, and the algorithm for finding optimum Huffman trees.

https://brilliant.org/wiki/greedy-algorithm/

# Classic Problems



