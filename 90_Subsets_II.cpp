/* Solution 1 */
/*
  We can treat duplicate element as a spacial element. 
  For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, 
  we can treat it as one special element 5, but this element has more than two choices: 
  you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. 
*/
class Solution {
public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> res = { {} } ;
    std::sort(nums.begin(),nums.end());
    int n(nums.size()), count(0);
    for (int i=0;i<n;) {
      // counting how many succeeding number are same as current number
      count = 0;
      while (i+count<n && nums[i+count] == nums[i]) ++ count;

      int pre_size = res.size();
      for (int j=0; j<pre_size; ++j) {
        vector<int> instance = res[j];
        for (int k=0;k<count;++k) {
          instance.push_back(nums[i]);
          res.push_back(instance);
        }
      }
      i += count;
    }
    return res;
  }
};

/* Solution 2 */
class Solution2 {
public:
  vector< vector<int> > subsetsWithDup(vector<int>& nums) {
    vector< vector<int> > res;
    std::sort(nums.begin(),nums.end());
    vector<int> temp;
    dfs(res,temp,nums,0);
    return res;
  }
private:
  // Consider start as a tree node, and the number after nums[start]
  // as its children, which means the branches it can enter.
  // Don't you agree that the longest branch will be visted at first?
  void dfs(vector<vector<int>> & res,
           vector<int> & temp,
           const vector<int> & nums,
           int start) {
    res.push_back(temp);
    for (int i=start;i<nums.size();++i) {
      if (i>start && nums[i]==nums[i-1]) continue; //ignore duplicates
      temp.push_back(nums[i]);
      dfs(res,temp,nums,i+1);
      temp.pop_back();
    }
  }
};
