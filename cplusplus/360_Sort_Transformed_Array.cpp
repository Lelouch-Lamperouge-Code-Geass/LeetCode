vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
  if(nums.size() ==0) return {};
  vector<int> result;
  int left = 0, right = nums.size()-1;
  auto func = [=](int x) { return a*x*x + b*x + c; };
  while(left <= right)
    {
      int val1 = func(nums[left]), val2 = func(nums[right]);
      if(a > 0) {
        result.push_back(val1>=val2?val1:val2);
        val1>val2? left++:right--;
      } else {
        result.push_back(val1>=val2?val2:val1);
        val1>val2? right--:left++;
      }
    }
  if(a > 0) reverse(result.begin(), result.end());
  return result;
}  
