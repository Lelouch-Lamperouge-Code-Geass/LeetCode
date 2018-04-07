There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

```2, [[1,0]]```

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

```4, [[1,0],[2,0],[3,1],[3,2]]```

There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].
  
Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about [how a graph is represented](https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs).
You may assume that there are no duplicate edges in the input prerequisites.  

# Solution

This question asks for an order in which prerequisite courses must be taken first. This prerequisite relationship reminds one of directed graphs. Then, the problem reduces to find a topological sort order of the courses, which would be a DAG if it has a valid order.

In the field of computer science, a __topological sort__ or __topological ordering__ of a __directed graph__ is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another; in this application, a topological ordering is just a valid sequence for the tasks. A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a __directed acyclic graph (DAG)__. Any DAG has at least one topological ordering, and algorithms are known for constructing a topological ordering of any DAG in linear time.


The usual algorithms for topological sorting have running time linear in the number of nodes plus the number of edges, asymptotically, __O(V + E)__ :

1. Kahn's algorithm
2. Depth-first search

### Solution 1 with Kahn's algorithm

We observe that if a node has incoming edges, it has prerequisites. Therefore, the first few in the order must be those with no prerequisites, i.e. no incoming edges. Any non-empty DAG must have at least one node without incoming links. You can draw a small graph to convince yourself. If we visit these few and remove all edges attached to them, we are left with a smaller DAG, which is the same problem. This will then give our BFS solution.

__Please note, we fist of all put all the zero-indegree nodes into the queue. If we only put one zero-indegree node, it will be a problem. Think about we have two zero-indegree nodes, and we push only one node as the begin node into the queue, and after take out it from the queue and reduce the indegree of its neighbors. It is possible that all its neighbors's indegree are all larger than zero. And another zero-indegree node has never been put into the queue.__


```cpp           
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector< vector<int> > graph(numCourses, vector<int>() );
    vector<int> indegree(numCourses,0);
    for(auto item : prerequisites){
      graph[item.second].push_back(item.first);
      ++ indegree[item.first];
    }
    std::queue<int> zero; // 0 indegree queue
    for(int i=0;i<numCourses;++i) if(!indegree[i]) zero.push(i);
    vector<int> res;
    for (int i = 0; i < numCourses; i++) {
      if( zero.empty() ) break;
      int course = zero.front();
      zero.pop();
      res.push_back(course);
      for(int nc : graph[course]){
        if( --indegree[nc] == 0) zero.push(nc);
      }
      -- indegree[course]; // it can't be 0 any more
    }
    return res.size() == numCourses ? res : vector<int>();
  }

};
``` 



### Solution 2 with DFS

Another way to think about it is the last few in the order must be those which are not prerequisites of other courses. Thinking it recursively means if one node has unvisited child node, you should visit them first before you put this node down in the final order array. This sounds like the post-order of a DFS. Since we are putting nodes down in the reverse order, we should reverse it back to correct ordering or use a stack.

__Note : 1. for the DFS part, we can only add the the course once its all children have been visited, and eventually we need to reverse the final result. 2. ```on_path[cid]``` must be checked before ```visited[cid]``` in the DFS part, otherwise it won't work. 

```cpp
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector< vector<int> > graph(numCourses, vector<int>() );
    for(auto item : prerequisites){
      graph[item.second].push_back(item.first);
    }
    vector<int> res;
    vector<bool> visited(numCourses,false), on_path(numCourses,false);
    for(int cid = 0; cid<numCourses; ++cid ){
      if( !visited[cid] && !dfs(res,cid,graph,visited,on_path) ) {
        // Not visited and can't make dfs without infinite loop
        return {};
      }
    }
    std::reverse(res.begin(),res.end());
    return res;
  }
private:
  // Return true if dfs succeed(no cycle).
  bool dfs(vector<int> & res,
           int cid, //course id
           vector< vector<int> > & graph,
           vector<bool> & visited,
           vector<bool> & on_path) {
    if(on_path[cid]) return false; // On the same dfs path
    if(visited[cid]) return true; // Visited, no need to go further
    visited[cid] = on_path[cid] = true;
    for(int num : graph[cid]){
      if( on_path[num] || !dfs(res,num,graph,visited,on_path)){
        // If the node has been on the recursive path,
        // or call dfs on it return false, we can return false directly
        // since a cycle has been detected.
        return false;
      }
    }
    res.push_back(cid); //push current course if all it's children have been added
    on_path[cid] = false; //rewind on_path
    return true;
  }
};
```  

Different style.

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector< vector<int> > graph(numCourses, vector<int>() );
        for(auto item : prerequisites){
          graph[item.second].push_back(item.first);
        }
        
        vector<int> result;
        vector<bool> visited(numCourses, false), on_path(numCourses, false);
        for (int i = 0; i < numCourses; ++i) {
            if (!visited[i]) {
                if (hasCircleInDFS(graph, i, visited, on_path, result)) {
                    // Detect a circle when searching with DFS
                    return vector<int>();
                }
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
private:
    bool hasCircleInDFS(vector< vector<int> > &graph,
            int course,
            vector<bool> &visited,
            vector<bool> &on_path,
            vector<int> &result) {
        if (on_path[course]) {
            return true;
        } else if (visited[course]) {
            return false;
        } else { // !visited[course] && !on_path[course]
            visited[course] = true;
            on_path[course] = true;
            for (int to : graph[course]) {
                if (hasCircleInDFS(graph, to, visited, on_path, result)) {
                    return true;
                }
            }
            on_path[course] = false;
            result.emplace_back(course);
            return false;
        }
    }
};
```



