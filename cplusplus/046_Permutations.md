Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:

```
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

# Solution

### Solution 1

The best way to handle permuation is using next permutation. __It even works for duplicates!__

```cpp
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
```

If you dont want to sort the vector which cost O(nlogn), we can get how many permutations we need at first. But __this works only when no duplicates involved__.

```
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> reval;
    int nums_size(nums.size());
    int permute_times(1);
    for (int i=1;i<=nums_size;++i) permute_times *= i;
    while (permute_times--) {
      std::next_permutation(nums.begin(),nums.end());
      reval.push_back(nums);
    }
    return reval;
};
```



### Solution 3

It is said that the collection has DISTINCT numbers so we don't neet to worrry duplicates.
Let's say that f[1,2,3] return the permutation results of [1,2,3]. Therefore, f[1,2,3] = (1,f[2,3]),(2,f[1,3]),(3,f[1,2]).
It's quite straghtforward that f[2,3] = (2,f[3]),(3,f[2])
     = (2,3),(3,2), of course f[2,3] = f[3,2].
     So the solution is: put each number at current position and move on to 
     next postion with rest numbers until all positions have been filled.

```cpp
  class Solution {
  public:
    vector<vector<int>> permute(vector<int>& nums) {
      vector<vector<int>> reval;
      vector<int> copy(nums);// optionally, depends whether input should be kept
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
        for (int i=pos;i<nums_size;++i) {
          std::swap(nums[pos],nums[i]);
          FillWithDfs(res,nums,pos+1);
          std::swap(nums[pos],nums[i]);
        }
      }
    }
  };
```  
