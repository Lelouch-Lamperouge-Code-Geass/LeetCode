Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

# Solution

The brute-force way to solve this problem is to calculate : ```min(height[left], height[right]) * (right - left) ``` for all different pairs of indexes in height vector. The time complexity is O(N^2).
  
How can we improve this brute-force solution?

If we use left and right pointers and do above calculation from both sides, we have an interesting observation : after the calcution   ```int cur_area = std::min(max_left_include_curr, max_right_include_curr) * (right - left);```,  should we increase ```left``` or decrease ```right```? Note that no matter we are increaing ```left``` or decreasing ```right```, we are reducing the width of formed container. Therefore, we must ensure a better possibility of getting a higher height. Therefore, we should increase/decrease the pointer which has lower height.

__In summary, start by evaluating the widest container, using the first and the last line. All other possible containers are less wide, so to hold more water, they need to be higher. Thus, after evaluating that widest container, skip lines at both ends that don't support a higher height. Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.__

### Solution one
  
  
```cpp  
class Solution {
public:
  int maxArea(vector<int>& height) {
    if (height.empty()) return 0;
    int max_area(0);
    std::size_t left(0),right(height.size()-1);
    while(left < right){
      int min_height = std::min(height[left],height[right]);
      int area = (right - left) * min_height;
      max_area = std::max(max_area,area);
      while (height[left] <= min_height && left < right) ++left;
      while (height[right] <= min_height && left < right) --right;
    }
    return max_area;
  }
};
```

### Solution two, same as solution one but with different coding style


```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        if (height.empty()) return 0;
        
        std::size_t left(0), right(height.size() - 1);
        int max_left_include_curr(0), max_right_include_curr(0); // All heights are non-negative
        
        int max_area(0);
        while (left < right) {
            max_left_include_curr = std::max(max_left_include_curr, height[left]);
            max_right_include_curr = std::max(max_right_include_curr, height[right]);
            
            int cur_area = std::min(max_left_include_curr, max_right_include_curr) * (right - left);
            max_area = std::max(max_area, cur_area);
            
            if (max_left_include_curr < max_right_include_curr) {
                ++ left;
            } else {
                -- right;
            }
        }
        
        return max_area;
    }
};
```
