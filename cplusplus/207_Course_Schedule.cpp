/*
 * Solution with BFS
*/
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

/*
 * Soution with DFS
 */
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
