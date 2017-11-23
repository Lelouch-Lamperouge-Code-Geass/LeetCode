Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

* First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
* Second node is labeled as 1. Connect node 1 to node 2.
* Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

```
       1
      / \
     /   \
    0 --- 2
         / \
         \_/
```

# Solution

_First of all, this problem's description needs more clarification. It gives you only one input graph node, which is implying that the whole graph is __connected__. This problem's title should be changed to "clone connected graph"._


This problem is an application of graph traversal, which has two systematic methods: Bread-First Search (BFS) and Depth-First Search (DFS).

We need to maintain a hashmap from original node to the "clone" node. And use BFS or DFS to visit original nodes. Everytime we visit an original node, we need to create the "clone" node if it is null. And we also need to create the clone nodes for its neighbors and generate the clone edges from the cloned-original node to the clone neighbors.  

__Note: we also need be careful about cycle and self-cycle.__

##### Solution with BFS

Instantiation clone node and push to queue. Clone edges for popped node.

Time complexity  O(|V|+|E|), space complexity  O(|V|+|E|).

```cpp
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return nullptr;
        
        // Kepp a node-to-clone_node one-on-one mapper
        std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> node_mapper;
        std::queue<UndirectedGraphNode*> bfs_queue;
        node_mapper[node] = new UndirectedGraphNode(node->label);
        bfs_queue.push(node);
        
        while (!bfs_queue.empty()) {
            UndirectedGraphNode *cur_node = bfs_queue.front();
            bfs_queue.pop();
            for (UndirectedGraphNode * neighbor : cur_node->neighbors) {
                if (!node_mapper[neighbor]) {
                    // If neighbor's clone is null, generated it
                    node_mapper[neighbor] = new UndirectedGraphNode(neighbor->label);
                    bfs_queue.push(neighbor);
                }
                node_mapper[cur_node]->neighbors.emplace_back(node_mapper[neighbor]);
            }
        }
        
        return node_mapper[node];
    }
};
```

##### Solution with DFS


```cpp
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return nullptr;
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode*> mapper;
        DFS(mapper, node);
        return mapper[node];
    }
private:
    void DFS(unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> &mapper,
             UndirectedGraphNode *node) {
        if (mapper.count(node) == 0) {
            // Here by instantiating the clone node, we actually "marked"
            // the original node as visited.
            mapper[node] = new UndirectedGraphNode(node->label);
            for (UndirectedGraphNode *neighbor : node->neighbors) {
                DFS(mapper, neighbor);
                mapper[node]->neighbors.emplace_back(mapper[neighbor]);
            }
        }
    }
};
```
