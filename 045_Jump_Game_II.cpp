class Solution {
public:
  int jump(vector<int>& nums) {
    int count(0),reach(0),next_reach(-1);
    for(int i=0;i<nums.size() && i<=reach;++i){
      next_reach = std::max(next_reach,i+nums[i]);
      if(i!=nums.size()-1 && i==reach){
        ++ count;
        reach = next_reach;
      }
    }
    return reach >= nums.size()-1 ? count : INT_MAX;
  }
};


/*
This problem can also be considered as  a BFS problem, where nodes in level i are all the nodes that can be reached in i-1th jump. for example. 2 3 1 1 4 , is
2||
3 1||
1 4 ||

clearly, the minimum jump of 4 is 2 since 4 is in level 3
*/
