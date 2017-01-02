class Solution {
public:
  void sortColors(vector<int>& nums) {
    int red(-1), blue(nums.size());

    for (int i=0;i<blue;) {
      if (i>red && nums[i]==0) {
        std::swap(nums[++red],nums[i]);
      } else if(i<blue &&nums[i]==2) {
        std::swap(nums[--blue],nums[i]);
      } else {
        // nums[i]==1 or can't swap i with red and blue anymore
        ++ i;
      }
    }
  }
};
