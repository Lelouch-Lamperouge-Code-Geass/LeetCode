/*
Start by evaluating the widest container, using the first and the last line. 
All other possible containers are less wide, so to hold more water, they need to be higher. 
Thus, after evaluating that widest container, skip lines at both ends that don't support a higher height. 
Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.
*/
class Solution {
public:
  int maxArea(vector<int>& height) {
    int max_area(0);
    std::size_t left(0),right(height.size()-1);
    while(left<right){
      int min_height = std::min(height[left],height[right]);
      int area = (right - left) * min_height;
      max_area = std::max(max_area,area);
      while (height[left] <= min_height && left < right) ++left;
      while (height[right] <= min_height && left < right) --right;
    }
    return max_area;
  }
};
