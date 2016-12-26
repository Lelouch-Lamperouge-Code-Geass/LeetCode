/* Solution 1 with BFS*/
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
/* Solution 2*/
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector< vector<int> > graph( numCourses,vector<int>() );
    vector<int> indegree(numCourses,0);
    for (const pair<int,int> & item : prerequisites) {
      graph[item.second].push_back(item.first);
      ++ indegree[item.first];
    }

    vector<int> res;
    for (int i=0;i<numCourses;++i) {
      int k = get_zero_indegree(indegree);
      if (k==-1) return vector<int>();
      for (int next : graph[k]) {
        -- indegree[next];
      }
      res.push_back(k);
    }
    return res;
  }
private:
  int get_zero_indegree (std::vector<int> & indegree) {
    std::vector<int>::iterator iter = std::find(indegree.begin(),indegree.end(),0);
    if (iter == indegree.end()) return -1;
    *iter = -1; // set its indegree to be -1
    return iter-indegree.begin(); //return index
  }
};
/* Solution 3 with DFS */
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
