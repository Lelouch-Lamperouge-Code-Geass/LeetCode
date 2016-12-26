/*
Here we may have duplicates.
So we can't use reference with swap anymore.
Let's say input is [1,2,2,3], first we handle [1]+f[2,2,3],
next we handle [2]+f[1,2,3], then how we keep going here 
from [2,1,2,3] ? It's hard to detect the duplicates here.
After we fill current postion, the rest of the vector should
keep sorted order otherwise it wont work.
Therefore, we are going to use value copy here to keep the original
input.
*/
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    std::sort(nums.begin(),nums.end());
    FillWithDfs(res,nums,0);
    return res;
  }
private:
  void FillWithDfs(vector<vector<int>> & res,
                   vector<int> nums,
                   int pos){
    const int nums_size(nums.size());
    if (pos == nums_size) {
      res.push_back(nums);
    } else {
      for (int i=pos;i<nums_size;++i) {
        // Can't use nums[i]==nums[i-1] to check duplicates,
        // since [1,2,2,3] => [2,1,2,3].
        // We just need to prevent swap the same value.
        if (i>pos&&nums[i]==nums[pos]) continue;
        std::swap(nums[pos],nums[i]);
        FillWithDfs(res,nums,pos+1);
        // should not swap back, the keypoint is to keep rest numbers
        // in sorted order
      }
    }
  }
};

/* Solution 2
Again, the best solution for permutaion is always using next_permustaion, that makes this much simpler
and fail-safe.*/
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int> > res;
    sort(nums.begin(), nums.end());
    res.push_back(nums);
    while (std::next_permutation(nums.begin(),nums.end()))
      res.push_back(nums);
    return res;
  }
};
/* Solution 3
Same as solution 2 */
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> reval;
    std::sort(nums.begin(),nums.end());
    reval.push_back(nums);
    while(nextPermutation(nums)){
      reval.push_back(nums);
    }
    return reval;
  }
private:
  bool nextPermutation(vector<int>& nums){
    int vio_index(nums.size()-2);
    while(vio_index>=0 && nums[vio_index] >= nums[vio_index+1]){
      -- vio_index;
    }
    if(vio_index == -1) return false;
    std::reverse(nums.begin()+vio_index+1, nums.end());
    //find the upper bound value
    auto iter = std::upper_bound(nums.begin()+vio_index+1,nums.end(),nums[vio_index]);
    std::swap(nums[vio_index],*iter);
    return true;
  }
};
