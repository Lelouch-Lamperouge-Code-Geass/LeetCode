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

                             
### Solution one :  BFS

```cpp                             
class Solution {
public:
  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> indegree(numCourses, 0);
    vector< vector<int> > graph(numCourses, vector<int>());
    for (const pair<int, int> & item : prerequisites) {
      ++indegree[item.first];
      graph[item.second].push_back(item.first);
    }

    int found(0);
    for (int i = 0; i < numCourses; ++i) {
      int course = get_zero_indegree(indegree);
      if (course == -1) return false;
      for (int next : graph[course]) {
        --indegree[next];
      }
      ++found;
    }
    return found == numCourses;
  }

private:
  int get_zero_indegree(vector<int>& indegree) {
    std::vector<int>::iterator iter =
      std::find(indegree.begin(), indegree.end(), 0);
    if (iter == indegree.end()) return -1;
    *iter = -1;
    return iter - indegree.begin();  // return index, which is the course number
  }
};
```

# Solution two : DFS

```cpp
class Solution {
public:

  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> graph(numCourses,vector<int>());

    for(const pair<int, int> & pre : prerequisites){
      graph[pre.second].push_back(pre.first);
    }
    vector<bool> visited(numCourses,false),onpath(numCourses,false);
    for(int i=0;i<numCourses;++i){
      if(!visited[i] && !dfs(i,graph,visited,onpath)){
        return false;
      }
    }
    return true;
  }
private:
  // Return value means DFS succeed or not. True means no cycle, false means it has a cycle.
  bool dfs(const int course,vector<vector<int>> & graph,vector<bool> & visited,vector<bool> & onpath){
    if(onpath[course]) return false; // On the same dfs path
    if(visited[course]) return true;  // Visited, no need to go further
    onpath[course] = visited[course] = true;
    for(const int num : graph[course]){
      if(onpath[num] || !dfs(num,graph,visited,onpath)){
        return false;
      }
    }
    onpath[course] = false;//rewind onpath status
    return true;
  }
};
```
