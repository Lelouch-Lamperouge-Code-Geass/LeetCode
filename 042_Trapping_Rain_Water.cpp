class Solution {
public:
  //Here is my idea: instead of calculating area by height*width,
  // we can think it in a cumulative way. In other words, sum water amount of each bin(width=1).
  // For each bin, the water it can contain = std::min(max_left,max_right) - cur_val.
  // That is to say, the water each bin can contain is limited by
  // minimal value between the max height of its left bars and the max height of its right bars.
  // So we can accumulate from both sides to its middle.
  int trap(vector<int>& height) {
    int reval(0),left(0),right(height.size()-1),max_left(0),max_right(0);
    while (left<right) {
      while (left<right && height[left]<=height[right]) {
        reval += std::max(0,max_left - height[left]);
        max_left = std::max(max_left,height[left]);
        ++ left;
      }
      while (left<right && height[left]>height[right]) {
        reval += std::max(0,max_right - height[right]);
        max_right = std::max(max_right,height[right]);
        -- right;
      }
    }
    return reval;
  }
};
/* A little bit variation */
class Solution {
public:
  //Here is my idea: instead of calculating area by height*width,
  // we can think it in a cumulative way. In other words, sum water amount of each bin(width=1).
  // For each bin, the water it can contain = std::min(max_left,max_right) - cur_val.
  // That is to say, the water each bin can contain is limited by
  // minimal value between the max height of its left bars and the max height of its right bars.
  // So we can accumulate from both sides to its middle.
  int trap(vector<int>& height) {
    int reval(0),left(0),right(height.size()-1),max_left(0),max_right(0);
    while (left<right) {
      if (height[left]<=height[right]) {
        reval += std::max(0,max_left - height[left]);
        max_left = std::max(max_left,height[left]);
        ++ left;
      } else {
        reval += std::max(0,max_right - height[right]);
        max_right = std::max(max_right,height[right]);
        -- right;
      }
    }
    return reval;
  }
};
