/*
Solution 1
 */
class Solution {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    CheckWithDfs(res,temp,candidates,target,0);
    return res;
  }
private:
  void CheckWithDfs(vector<vector<int>> & res,
                    vector<int> & temp,
                    const vector<int> & candidates,
                    int target,
                    int start){
    if (target==0 &&!temp.empty()) {
      res.push_back(temp);
    } else {
      for (int i=start;i<candidates.size();++i) {
        if (target - candidates[i] < 0 ) continue;
        temp.push_back(candidates[i]);
        CheckWithDfs(res,temp,candidates,target - candidates[i],i);
        temp.pop_back();
      }
    }
  }
};

/* Solution 2*/
class Solution {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    helper(res,temp,candidates,0,target);
    return res;
  }
private:
  void helper(vector<vector<int>> & res,
              vector<int> & temp,
              const vector<int>& candidates,
              int start,
              int target){
    if(start == candidates.size() && target==0 && !temp.empty()){
      res.push_back(temp);
    } else {
      if(start >= candidates.size()) return;
      //choose current element
      if(target-candidates[start]>=0){
        temp.push_back(candidates[start]);
        helper(res,temp,candidates,start,target-candidates[start]);
        temp.pop_back();//revert back
      }
      //not choose current element
      helper(res,temp,candidates,start+1,target);
    }
  }
};
