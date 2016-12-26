/*
Solution 1.
It is said that the collection has DISTINCT numbers so we don't neet to 
worrry duplicates.
Let's say that f[1,2,3] return the permutation results of [1,2,3].
Therefore, f[1,2,3] = (1,f[2,3]),(2,f[1,3]),(3,f[1,2]).
It's quite straghtforward that f[2,3] = (2,f[3]),(3,f[2])
= (2,3),(3,2), of course f[2,3] = f[3,2].
So the solution is: put each number at current position and move on to 
next postion with rest numbers until all positions have been filled.
*/
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> reval;
    FillWithDfs(reval,copy,0);
    return reval;
  }
private:
  void FillWithDfs(vector< vector<int> > & res,
                   vector<int> & nums,
                   int pos){
    const int nums_size(nums.size());
    if (pos == nums_size) {
      res.push_back(nums);
    } else {
      for (int i=pos;i<nums_size();++i) {
        std::swap(nums[pos],nums[i]);
        FillWithDfs(res,nums,pos);
        std::swap(nums[pos],nums[i]); // Mandatory, remeber, this is DFS.
      }
    }
  }
};

/*
Solution 2
The best way to handle permuation is using next permutation.
It works even for duplicates.
Other solutions suck.
*/
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> reval;
    std::sort(nums.begin(),nums.end());
    reval.push_back(nums);
    while (std::next_permutation(nums.begin(),nums.end())) {
      reval.push_back(nums);
    }
    return reval;
  }
};
