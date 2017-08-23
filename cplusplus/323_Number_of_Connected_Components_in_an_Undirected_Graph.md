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
