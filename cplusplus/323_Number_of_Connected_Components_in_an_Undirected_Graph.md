Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

Example 1:

```
     0          3
     |          |
     1 --- 2    4
```
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.
  

Example 2:
```
     0           4
     |           |
     1 --- 2 --- 3
```
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

# Solution

To find the number of connected components. We can use:

1. BFS
2. DFS
3. Union-find(disjoint-set)

According to CLRS, When the edges of the graph are static—not changing over time—we can compute the connected components faster by using depth-first search.

When the edges of the graph are dynamic – changing over time – DFS is not a good choice since it cannot be applied progressively, we need to use a data structure to represents the graph(represented in adjacent lists or adjacent matrix) first.

And in this condition, we can compute the connected components faster by using union-find.

__In summary, prefer using BFS or DFS when graph is static; prefer using union-find when graph is dynamic.__

```cpp
int countComponents(int n, vector<pair<int, int>>& edges) {
  std::vector<int> parents(n, 0);
  std::iota(parents.begin(), parents.end(), 0);

  int reval(n);

  for (const pair<int, int> &edge : edges) {
    int from = edge.first;
    int to = edge.second;

    while (parents[from] != from) {
      parents[from] = parents[parents[from]]; // compress path
      from = parents[from];
    }

    while (parents[to] != to) {
      parents[to] = parents[parents[to]]; // compress path
      to = parents[to];
    }

    parents[to] = parents[from];

    if (from != to) -- reval; // ignore if the edge is a loop(points to self)
  }

  return reval;
}

void UnitTest() {
  vector<pair<int, int>>  edges = {{0,1}, {1,2}, {3,4}};
  assert(countComponents(5, edges) == 2);
  edges = {{0,1}, {1,2}, {2,3}, {3,4}};
  assert(countComponents(5, edges) == 1);
}


```

Simplify it here.

```cpp  
int countComponents(int n, vector<pair<int, int>>& edges) {
  vector<int> p(n);
  iota(begin(p), end(p), 0);
  for (auto& edge : edges) {
    int v = edge.first, w = edge.second;
    while (p[v] != v) v = p[v] = p[p[v]];
    while (p[w] != w) w = p[w] = p[p[w]];
    p[v] = w;
    n -= v != w;
  }
  return n;
}
```

# Knowledge

### Connected component

In graph theory, a connected component (or just component) of an undirected graph is a subgraph in which any two vertices are connected to each other by paths, and which is connected to no additional vertices in the supergraph.

It is straightforward to compute the connected components of a graph in linear time (in terms of the numbers of the vertices and edges of the graph) using either __breadth-first search__ or __depth-first search__. In either case, a search that begins at some particular vertex v will find the entire connected component containing v (and no more) before returning. To find all the connected components of a graph, loop through its vertices, starting a new breadth first or depth first search whenever the loop reaches a vertex that has not already been included in a previously found connected component. 

There are also efficient algorithms to dynamically track the connected components of a graph as vertices and edges are added, as a straightforward application of __disjoint-set data structures__. 



