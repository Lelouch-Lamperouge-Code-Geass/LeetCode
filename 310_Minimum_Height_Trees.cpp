/**
The basic idea is "keep deleting leaves layer-by-layer, until reach the root."

Specifically, first find all the leaves, then remove them. 
After removing, some nodes will become new leaves. So we can continue remove them. 
Eventually, there is only 1 or 2 nodes left. If there is only one node left, it is the root. 
If there are 2 nodes, either of them could be a possible root.

Time Complexity: Since each node will be removed at most once, the complexity is O(n).
 **/
class Solution {
public:
  vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
    if (n==1) return vector<int> (1,0);
    unordered_map<int,unordered_set<int>> adj;
    for (const pair<int, int> & edge : edges) {
      adj[edge.first].insert(edge.second);
      adj[edge.second].insert(edge.first);
    }

    vector<int> leaves;
    for (const auto & item : adj) {
      if (item.second.size()==1) {
        leaves.push_back(item.first);
      }
    }

    while (n>2) {
      vector<int> next_leaves;
      n -= leaves.size();
      for (int leaf : leaves) {
        int neighbor = *adj[leaf].begin();//leaf node only has one neighbor
        adj[leaf].erase(neighbor);
        adj[neighbor].erase(leaf);
        if (adj[neighbor].size()==1) {
          next_leaves.push_back(neighbor);
        }
      }
      leaves = next_leaves;
    }
    return leaves;
  }
};
