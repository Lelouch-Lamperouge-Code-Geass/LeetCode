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
