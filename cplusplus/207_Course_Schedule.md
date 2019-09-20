There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

```2, [[1,0]]```

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
  
```2, [[1,0],[0,1]]```

There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
  
Note:

* The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.  
* You may assume that there are no duplicate edges in the input prerequisites.   
  
Hints:

* This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
* [Topological Sort via DFS](https://www.coursera.org/specializations/algorithms) - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
* Topological sort could also be done via BFS.

# Solution
                             
### Solution one :  Kahn’s algorithm

This solution is based on the fact that we can only begin with a course that as no prerequisites. It's intuitive to relate this type of problems to graph. And the course here that has no prerequisites are basically the nodes that have zero in-degree. So we begin with such node(course), and after take this node(course), we can minus the indegree of those courses(graph nodes) that are depended on this course. Eventually we can complete as far as we can, and we compare the course we complete with the total amount of course, if it is less than that then we can't complete all the course.

[Kahn’s algorithm for Topological Sorting](http://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)


Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge uv, vertex u comes before v in the ordering. Topological Sorting for a graph is not possible if the graph is not a DAG.

For example, a topological sorting of the following graph is “5 4 2 3 1 0?. There can be more than one topological sorting for a graph. For example, another topological sorting of the following graph is “4 5 2 0 3 1″. The first vertex in topological sorting is always a vertex with in-degree as 0 (a vertex with no in-coming edges).

![alt](http://www.geeksforgeeks.org/wp-content/uploads/graph.png)

A DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0.

Proof: There’s a simple proof to the above fact is that a DAG does not contain a cycle which means that all paths will be of finite length. Now let S be the longest path from u(source) to v(destination). Since S is the longest path there can be no incoming edge to u and no outgoing edge from v, if this situation had occurred then S would not have been the longest path
=> indegree(u) = 0 and outdegree(v) = 0

##### Algorithm:
Steps involved in finding the topological ordering of a DAG:

* Step-1: Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and initialize the count of visited nodes as 0.

* Step-2: Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)

* Step-3: Remove a vertex from the queue (Dequeue operation) and then.
  * Increment count of visited nodes by 1.
  * Decrease in-degree by 1 for all its neighboring nodes.
  * If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
* Step 4: Repeat Step 3 until the queue is empty.
* Step 5: If count of visited nodes is not equal to the number of nodes in the graph then the topological sort is not possible for the given graph.


```cpp                             
class Solution {
public:

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector< vector<int> > graph(numCourses, vector<int>() );
        vector<int> indegree(numCourses,0);
        for(const auto &item : prerequisites){
          graph[item.second].push_back(item.first);
          ++ indegree[item.first];
        }
        
        // put all the zero-indegree nodes into queue
        std::queue<int> zero; // 0 indegree queue
        for(int i = 0;i < numCourses; ++i) {
            if(!indegree[i]) zero.push(i);
        }
        
        // begin BFS
        int found(0);
        for (int i = 0; i < numCourses; i++) {
          if( zero.empty() ) break;
          int course = zero.front();
          zero.pop();
          for(int nc : graph[course]){
            if( --indegree[nc] == 0) zero.push(nc);
          }
          -- indegree[course]; // it can't be 0 any more
          ++ found;
        }
        return found == numCourses;
    }

    
};
```

### Solution two : DFS

The idea is that we can't not complete the courses only when there is a cycle in the graph. How to detect a cycle? DFS.

At beginning, we mark all nodes un-visited. We can keep beginning with any random graph node, and perform DFS from it, if there is a cycle, then we can just return false because it's clear that we can't complete all of them. We do this untill all nodes are visited.

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        // Build graph
        std::vector<std::unordered_set<int>> graph(numCourses, std::unordered_set<int>());
        for (const auto &pair_item : prerequisites) {
            graph[pair_item.first].insert(pair_item.second);
        }
        // Visit each node with DFS
        std::vector<bool> visited(numCourses, false), in_circle(numCourses, false);
        for (int course_id = 0; course_id < numCourses; ++ course_id) {
            if (hasCircle(visited, in_circle, course_id, graph)) {
                return false;
            }
        }
        
        return true;
    }
    
private:
    bool hasCircle(std::vector<bool> &visited, 
                   std::vector<bool> &in_circle, 
                   int course_id, 
                   const std::vector<std::unordered_set<int>> &graph){
        // If you switch these two IF clause, it won't work.
        // e.g. [0,1], [1,0]
        if (in_circle[course_id]) return true;
        if (visited[course_id]) return false;
        
        visited[course_id] = in_circle[course_id] = true;
        
        for (int next : graph[course_id]) {
            if (hasCircle(visited, in_circle, next, graph)) {
                return true;
            }
        }
        
        in_circle[course_id] = false; // Need revert back for next usage
        return false;
    }
};
```
