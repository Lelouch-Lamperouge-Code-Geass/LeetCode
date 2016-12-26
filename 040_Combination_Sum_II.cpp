/*
For each number, we have two options, choose or not choose.
This can form a decision tree.
For each tree node, if its sum is equal to target, we can add 
it to final result.
f[1,1,1,2,2] = (1 , f[1,1,2,2]),
               (1,f[1,2,2]),
               (1,f[2,2]),
               (2,f[2]),
               (2,f[])
Here, the second and thrid item are the subset of f[1,1,2,2].
The final item is the subset fourth item.
*/

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    std::sort(candidates.begin(),candidates.end());
    dfs(res,temp,candidates,target,0);
    return res;
  }
private:
  void dfs(vector<vector<int>> & res,
           vector<int> & temp,
           const vector<int> & candidates,
           int target,
           int start){
    if (target==0) {
      res.push_back(temp);
    } else {
      for (int i=start;i<candidates.size();++i) {
        if (target<candidates[i]) break;
        if (i>start && candidates[i]==candidates[i-1]) continue;
        temp.push_back(candidates[i]);
        dfs(res,temp,candidates,target-candidates[i],i+1);
        temp.pop_back();
      }
    }
  }
};
