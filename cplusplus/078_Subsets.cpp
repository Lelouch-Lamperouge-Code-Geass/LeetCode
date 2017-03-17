/*
Backtracking solution
*/
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector< vector<int> > reval;
    vector<int> temp;
    Backtracking(reval,temp,nums,0);
    return reval;
  }
private:
  // quite similar to decision tree.
  // each level/index decide whether choose that number or not.
  // let's say go to left child means choose while go to right child means not choose that number.
  // the whole process is depth first.
  void Backtracking(vector< vector<int> > & reval,
              vector<int> & temp,
              vector<int> & nums,
              int index) {
    if (index ==  nums.size() ) {
      reval.push_back(temp);
    } else {
      // choose current number, go to left child
      temp.push_back(nums[index]);
      Backtracking(reval,temp,nums,index+1);
      temp.pop_back(); // revert back

      // not choose current number, go to right child
      Backtracking(reval,temp,nums,index+1);
    }
  }
};

/*
Iterative solution.
*/
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res(1,vector<int>());
    for (int num : nums) {
      const std::size_t pre_size(res.size());
      for (std::size_t i=0;i<pre_size;++i) {
        res.push_back(res[i]);
        res.back().push_back(num);
      }
    }
    return res;
  }
};
