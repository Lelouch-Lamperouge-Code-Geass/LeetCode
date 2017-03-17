class Solution {
public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> reval;
    int low(0),high(numbers.size()-1);
    while(low<high){
      int sum(numbers[low]+numbers[high]);
      if(sum==target){
        reval.push_back(low+1);
        reval.push_back(high+1);
        return reval;
      } else if(sum>target){
        -- high;
      } else {
        ++ low;
      }
    }
    return reval;
  }
};
